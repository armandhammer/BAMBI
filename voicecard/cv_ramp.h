// Copyright 2026 BAMBI contributors.
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
//
// -----------------------------------------------------------------------------
//
// YAM+ control-voltage ramps and the BAMBI filter-mode declicker, split out
// of voicecard.cc so the native tests can drive them with a simulated ISR.
//
// The main loop computes cutoff, resonance and VCA once per block (40
// samples). The ISR ramps each CV to its new value in kCvRampSteps steps,
// one every kCvDecimation samples (32 samples in all, less than a block).
//
// BAMBI: a new ramp starts from the value the ISR has reached, not from the
// previous target. When a block comes early (the main loop catching up after
// a slow block, so the previous ramp hasn't finished), the old code computed
// the step from the previous target and the ISR snapped the unfinished part
// of the old ramp onto the CV at the end of the new one: a step, i.e. a
// click on the VCA. Likewise an unchanged VCA no longer cuts a ramp short.

#ifndef VOICECARD_CV_RAMP_H_
#define VOICECARD_CV_RAMP_H_

#include "avrlib/base.h"

namespace ambika {

#ifndef CV_DECIMATION
#define CV_DECIMATION 4  // 1, 2, 4 or 8.
#endif

static const uint8_t kCvDecimation = CV_DECIMATION;
static const uint8_t kCvRampSamples = 32;
static const uint8_t kCvRampSteps = kCvRampSamples / kCvDecimation;
static const uint8_t kCvRampShift = kCvRampSteps == 32 ? 5 :
    kCvRampSteps == 16 ? 4 : kCvRampSteps == 8 ? 3 : 2;

struct CvRamp {
  uint16_t value;  // Current value (ISR).
  uint16_t target;  // End of the ramp (written by the main loop).
  int16_t step;
};

// ISR side: one ramp step; the last one lands exactly on the target.
static inline void AdvanceRamp(CvRamp* ramp, uint8_t last) {
  ramp->value = last ? ramp->target : ramp->value + ramp->step;
}

// Main-loop side, with interrupts off: ramp from where the ISR is now.
// The step is |target - value| >> n with the sign of the difference: 16-bit
// shifts, no division (a 32-bit division is a ~600-cycle library call,
// longer than an ISR period with interrupts off). Truncating towards zero
// means the ramp never passes the target; the last step lands on it.
static inline void RetargetRamp(CvRamp* ramp, uint16_t target) {
  uint16_t value = ramp->value;
  ramp->step = target >= value ?
      static_cast<int16_t>((target - value) >> kCvRampShift) :
      -static_cast<int16_t>((value - target) >> kCvRampShift);
  ramp->target = target;
}

// Main-loop side of the VCA ramp, with interrupts off. Returns the number
// of ISR steps to run: a full ramp to a new value; for an unchanged value,
// whatever is left of the running ramp, or 1 to refresh the DAC once per
// block (as YAM did).
static inline uint8_t StartVcaRamp(
    CvRamp* ramp,
    uint8_t steps_left,
    uint16_t target) {
  if (target == ramp->target) {
    return steps_left ? steps_left : 1;
  }
  RetargetRamp(ramp, target);
  return kCvRampSteps;
}

// BAMBI: switching the SVF's LP/BP/HP/notch output while the voice sounds
// jumps between outputs with different levels and DC offsets (a click).
// When the mode changes on a sounding voice, the VCA is first ramped to 0,
// the mode is switched once the ramp has finished (a block later, ~1 ms),
// and the VCA ramps back up. A silent voice switches at once.
class FilterModeDeclicker {
 public:
  FilterModeDeclicker() : current_(0xff), last_level_(0) { }

  // Called once per block with the voice's VCA level (0-255, before the
  // log/linear DAC conversion: DAC 0 is full gain with the log VCA) and
  // whether the ISR has finished the previous VCA ramp. Returns the mode to
  // write to the mode port now, or 0xff for none; sets |*level| to 0 while
  // a switch waits for silence.
  uint8_t Update(uint8_t requested, uint8_t* level, uint8_t vca_ramp_idle) {
    requested &= 3;  // LP, BP, HP, notch: never past the mux inputs.
    uint8_t write = 0xff;
    if (requested != current_) {
      if (current_ == 0xff || (last_level_ == 0 && vca_ramp_idle)) {
        current_ = requested;
        write = requested;
      } else {
        *level = 0;
      }
    }
    last_level_ = *level;
    return write;
  }

  uint8_t current() const { return current_; }

 private:
  uint8_t current_;
  uint8_t last_level_;  // Level sent with the previous block.
};

}  // namespace ambika

#endif  // VOICECARD_CV_RAMP_H_
