// Copyright 2011 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include <avr/interrupt.h>

#include "voicecard/voicecard.h"

#include "avrlib/boot.h"
#include "avrlib/gpio.h"
#include "avrlib/parallel_io.h"
#include "avrlib/timer.h"

#include "common/atomic.h"
#include "voicecard/audio_out.h"
#include "voicecard/cv_ramp.h"
#include "voicecard/leds.h"
#include "voicecard/load_probe.h"
#include "voicecard/resources.h"
#include "voicecard/voice.h"
#include "voicecard/voicecard_rx.h"

using namespace avrlib;
using namespace ambika;

static const uint8_t kPinVcaOut = 3;
static const uint8_t kPinVcfResonanceOut = 5;
static const uint8_t kPinVcfCutoffOut = 6;

PwmOutput<kPinVcfCutoffOut> vcf_cutoff_out;
PwmOutput<kPinVcfResonanceOut> vcf_resonance_out;
PwmOutput<kPinVcaOut> vca_out;

ParallelPort<PortC, PARALLEL_TRIPLE_LOW> vcf_mode;

Gpio<PortB, 0> log_vca;

UartSpiMaster<UartSpiPort0, Gpio<PortD, 2>, 2> dac_interface;

static const uint8_t dac_scale = 16;

// -----------------------------------------------------------------------------
// YAM+ control-voltage smoothing (ramps: voicecard/cv_ramp.h).
//
// The voice computes cutoff, resonance and VCA once per block (40 samples,
// ~980 Hz). Writing them as steps zippers slow sweeps (8-bit cutoff PWM) and
// stair-steps fast envelopes. Instead, the main loop hands each new block
// value to the ISR, which ramps to it linearly in kCvRampSteps steps, one
// every kCvDecimation samples (~9.8 kHz), i.e. over 32 samples (< 1 block):
// - cutoff and resonance: 8.8 fixed point. The cutoff PWM duty is dithered
//   with first-order error feedback every sample, so the CV low-pass on the
//   voicecard averages it to sub-LSB resolution.
// - VCA: 12-bit DAC value (after linearization), written at every ramp step,
//   plus once per block when it doesn't change (like YAM).
// Unchanged values don't start a ramp, so a static voice costs only the
// divider and the dither in the ISR. BAMBI: ramps start from the value the
// ISR has reached (no step when a block comes early).
// -----------------------------------------------------------------------------

static CvRamp cutoff_ramp;
static CvRamp resonance_ramp;
static CvRamp vca_ramp = { 4095, 4095, 0 };  // Init() sets the DAC to 4095.
static uint8_t filter_ramp_steps;  // Filter CV ramp steps left.
static uint8_t vca_ramp_steps;  // VCA ramp steps (DAC writes) left.

// Called by the main loop after each block.
static inline void StartCvRamps(
    uint16_t cutoff,
    uint16_t resonance,
    uint16_t vca) {
  uint8_t filter_changed = cutoff != cutoff_ramp.target ||
      resonance != resonance_ramp.target;
  uint8_t sreg = InterruptsOff();
  if (filter_changed) {
    RetargetRamp(&cutoff_ramp, cutoff);
    RetargetRamp(&resonance_ramp, resonance);
    filter_ramp_steps = kCvRampSteps;
  }
  vca_ramp_steps = StartVcaRamp(&vca_ramp, vca_ramp_steps, vca);
  InterruptsRestore(sreg);
}

ISR(TIMER2_OVF_vect) {
  static uint8_t sample_counter = 0;
  static uint8_t cv_divider = 0;
  static uint8_t cutoff_dither = 0;
  
  if (++cv_divider >= kCvDecimation) {
    cv_divider = 0;
    uint8_t steps = filter_ramp_steps;
    if (steps) {
      filter_ramp_steps = --steps;
      AdvanceRamp(&cutoff_ramp, steps == 0);
      AdvanceRamp(&resonance_ramp, steps == 0);
      vcf_resonance_out.Write(resonance_ramp.value >> 8);
    }
    steps = vca_ramp_steps;
    if (steps) {
      vca_ramp_steps = --steps;
      AdvanceRamp(&vca_ramp, steps == 0);
      Word vca_12bits;
      vca_12bits.value = vca_ramp.value | 0x1000;
      dac_interface.Strobe();
      dac_interface.Overwrite(vca_12bits.bytes[1]);
      dac_interface.Overwrite(vca_12bits.bytes[0]);
      dac_interface.Wait();
    }
  }
  
  Word cutoff;
  cutoff.value = cutoff_ramp.value + cutoff_dither;
  cutoff_dither = cutoff.bytes[0];
  vcf_cutoff_out.Write(cutoff.bytes[1]);

  if (!audio_buffer.readable() && LoadProbe::underruns != 255) {
    ++LoadProbe::underruns;
  }
  uint8_t sample = audio_buffer.ImmediateRead();
  if (++sample_counter >= voice.crush()) {
    dac_interface.Strobe();
    sample_counter = 0;
    Word sample_12bits;
    sample_12bits.value = (sample * dac_scale) | 0x9000;
    dac_interface.Overwrite(sample_12bits.bytes[1]);
    dac_interface.Overwrite(sample_12bits.bytes[0]);
  }
  voicecard_rx.Receive();
}

// This GPIO is used during development for timing code.
Gpio<PortD, 7> timing_signal;

inline void Init() {
  sei();
  UCSR0B = 0;
  ResetWatchdog();
  
  dac_interface.Init();

  rx_led.set_mode(DIGITAL_OUTPUT);
  note_led.set_mode(DIGITAL_OUTPUT);
  rx_led.Low();
  note_led.Low();
  
  vcf_cutoff_out.Init();
  vcf_resonance_out.Init();
  vca_out.Init();
  vcf_mode.set_mode(DIGITAL_OUTPUT);

  voicecard_rx.Init();
  voice.Init();
  
  log_vca.set_mode(DIGITAL_INPUT);
  log_vca.High();
  dac_interface.Strobe();
  dac_interface.Overwrite(0x10 | 0x0f);
  dac_interface.Overwrite(0xff);
  
  // Successful boot!
  if (eeprom_read_byte(kFirmwareUpdateFlagPtr) != FIRMWARE_UPDATE_DONE) {
    eeprom_write_byte(kFirmwareUpdateFlagPtr, FIRMWARE_UPDATE_DONE);
  }
  
  // Initialize all the PWM outputs to 39kHz, phase correct mode.
  Timer<0>::set_prescaler(1);
  Timer<0>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<1>::set_prescaler(1);
  Timer<1>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::set_prescaler(1);
  Timer<2>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::Start();
}

static FilterModeDeclicker filter_mode_declicker;
static uint8_t leds_timeout = 0;

int main(void) {
  Init();
  // For testing only...
  // voice.Trigger(60 * 128, 100, 0);
  uint8_t load_probe_armed = 0;
  while (1) {
    // Check if there's a block of samples to fill.
    if (audio_buffer.writable() >= kAudioBlockSize) {
      uint8_t queued = audio_buffer.readable();
      voicecard_rx.TickRxLed();
      voice.ProcessBlock();
      // BAMBI: a filter mode change on a sounding voice fades the VCA out
      // and switches once it is silent (cv_ramp.h). The mode is masked to
      // the four SVF outputs (YAM indexed a 4-byte RAM table with it).
      uint8_t level = voice.vca();
      uint8_t mode = filter_mode_declicker.Update(
          voice.patch().filter[0].mode, &level, vca_ramp_steps == 0);
      if (mode != 0xff) {
        vcf_mode.Write(mode);
      }
      uint16_t vca;
      if (log_vca.is_low()) {
        vca = ambika::ResourcesManager::Lookup<uint16_t, uint8_t>(
            lut_res_vca_linearization,
            level);
      } else {
        vca = level * dac_scale;
      }
      StartCvRamps(voice.cutoff_cv(), voice.resonance_cv(), vca);
      // Samples played by the ISR while this block was computed.
      uint8_t played = queued + kAudioBlockSize - audio_buffer.readable();
      if (!load_probe_armed) {
        // Ignore the start-up period, when the buffer is still empty.
        LoadProbe::Clear();
        load_probe_armed = 1;
      } else if (played > LoadProbe::peak_block_samples) {
        LoadProbe::peak_block_samples = played;
      }
    }
    voicecard_rx.Process();
  }
}
