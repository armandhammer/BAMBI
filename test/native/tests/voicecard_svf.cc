// SVF voicecard DSP and control paths through the real Voice code: cutoff
// and resonance CV scaling and clipping at the extremes of every hardwired
// and matrix modulation, the crush divider range, and the mixer staying
// inside the 8-bit sample range (a wrap would be a full-scale click).
#include "test.h"
#include "voicecard_env.h"

#include <stddef.h>
#include <stdlib.h>
#include <vector>
#include <avr/pgmspace.h>

#include "common/patch.h"
#include "voicecard/voice.h"

using namespace ambika;

namespace {

uint16_t Note(uint8_t midi_note) { return midi_note << 7; }

void Set(size_t offset, uint8_t value) { native_vc::SetPatch(offset, value); }

// A sustained note with env 2 (-> cutoff) at its maximum.
void Sustain(uint8_t note, uint8_t velocity) {
  for (uint8_t e = 0; e < 3; ++e) {
    uint8_t base = offsetof(Patch, env_lfo) + e * sizeof(EnvelopeLfoSettings);
    Set(base + offsetof(EnvelopeLfoSettings, attack), 0);
    Set(base + offsetof(EnvelopeLfoSettings, sustain), 127);
  }
  native_vc::Render(1);
  voice.Trigger(Note(note), velocity, 0);
  native_vc::Render(60);
}

// Routes |source| to |destination| at |amount| in matrix slot |slot|.
void Route(uint8_t slot, uint8_t source, uint8_t destination, int8_t amount) {
  size_t base = offsetof(Patch, modulation) + slot * sizeof(Modulation);
  Set(base + offsetof(Modulation, source), source);
  Set(base + offsetof(Modulation, destination), destination);
  Set(base + offsetof(Modulation, amount), static_cast<uint8_t>(amount));
}

}  // namespace

TEST(SvfCutoffClipsHighInsteadOfWrapping) {
  // Everything pushing the cutoff up at once: the CV pins at the top of the
  // PWM range rather than wrapping round to a low value.
  for (int vintage = 0; vintage <= 127; vintage += 127) {
    for (uint8_t slot = 0; slot < 6; ++slot) {
      native_vc::Reset(slot);
      Set(offsetof(Patch, filter[0].cutoff), 127);
      Set(offsetof(Patch, filter_env), 63);
      Set(offsetof(Patch, filter_lfo), 63);
      Set(offsetof(Patch, filter_velo), 63);
      Set(offsetof(Patch, filter_kbt), 63);
      Set(offsetof(Patch, vintage), vintage);
      Route(0, MOD_SRC_CONSTANT_256, MOD_DST_FILTER_CUTOFF, 63);
      Route(1, MOD_SRC_CONSTANT_256, MOD_DST_FILTER_CUTOFF, 63);
      Sustain(120, 254);
      if (vintage == 0) {
        CHECK_MSG(voice.cutoff_cv() == 0xff00, "slot %d: %04x", slot,
                  voice.cutoff_cv());
        CHECK_EQ(voice.cutoff(), 255);
      } else {
        // A slot's cutoff tolerance (up to -3 steps of 128, plus drift)
        // applies after the clip, so its top end sits a little lower.
        CHECK_MSG(voice.cutoff_cv() >= 0xf000, "slot %d vintage: %04x", slot,
                  voice.cutoff_cv());
      }
    }
  }
}

TEST(SvfCutoffClipsLowInsteadOfWrapping) {
  for (int vintage = 0; vintage <= 127; vintage += 127) {
    for (uint8_t slot = 0; slot < 6; ++slot) {
      native_vc::Reset(slot);
      Set(offsetof(Patch, filter[0].cutoff), 0);
      Set(offsetof(Patch, filter_env), 0);  // The default patch has 63.
      // Key tracking is centred on note 64: +63 at note 0 pulls down.
      Set(offsetof(Patch, filter_kbt), 63);
      Set(offsetof(Patch, vintage), vintage);
      Route(0, MOD_SRC_CONSTANT_256, MOD_DST_FILTER_CUTOFF, -63);
      Route(1, MOD_SRC_CONSTANT_256, MOD_DST_FILTER_CUTOFF, -63);
      Sustain(0, 2);
      if (vintage == 0) {
        CHECK_MSG(voice.cutoff_cv() == 0, "slot %d: %04x", slot,
                  voice.cutoff_cv());
      } else {
        // Tolerance after the clip: a slot's floor sits a little higher.
        CHECK_MSG(voice.cutoff_cv() <= 0x1000, "slot %d vintage: %04x", slot,
                  voice.cutoff_cv());
      }
    }
  }
}

TEST(SvfCutoffRisesWithTheCutoffKnobAndTheNote) {
  int previous = -1;
  for (int cutoff = 0; cutoff <= 127; ++cutoff) {
    native_vc::Reset();
    Set(offsetof(Patch, filter[0].cutoff), cutoff);
    Sustain(60, 127);
    CHECK_MSG(voice.cutoff_cv() >= previous, "cutoff %d: %04x < %04x",
              cutoff, voice.cutoff_cv(), previous);
    previous = voice.cutoff_cv();
  }
  previous = -1;
  for (int note = 0; note <= 120; note += 4) {
    native_vc::Reset();
    Set(offsetof(Patch, filter[0].cutoff), 40);
    Sustain(note, 127);
    CHECK(voice.cutoff_cv() >= previous);
    previous = voice.cutoff_cv();
  }
}

TEST(SvfResonanceScalingAndClipping) {
  // Patch resonance 0-63 maps monotonically onto PWM duty 0-252/255 (stock
  // scaling); matrix modulation can reach 0xff00, never wraps.
  int previous = -1;
  for (int reso = 0; reso <= 63; ++reso) {
    native_vc::Reset();
    Set(offsetof(Patch, filter[0].resonance), reso);
    Sustain(60, 127);
    int cv = voice.resonance_cv();
    CHECK_EQ(cv, reso << 10);  // (reso << 8) << 2: 14-bit CV to 8.8 PWM.
    CHECK(cv >= previous);
    previous = cv;
  }
  CHECK_EQ(previous >> 8, 252);
  native_vc::Reset();
  Set(offsetof(Patch, filter[0].resonance), 63);
  Route(0, MOD_SRC_CONSTANT_256, MOD_DST_FILTER_RESONANCE, 63);
  Sustain(60, 127);
  CHECK_EQ(voice.resonance_cv(), 0xff00);
  native_vc::Reset();
  Set(offsetof(Patch, filter[0].resonance), 0);
  Route(0, MOD_SRC_CONSTANT_256, MOD_DST_FILTER_RESONANCE, -63);
  Sustain(60, 127);
  CHECK_EQ(voice.resonance_cv(), 0);
}

TEST(SvfCrushDividerStaysInRange) {
  // Sample-rate reduction: the ISR holds every Nth sample, N = 1..64.
  for (int crush = 0; crush <= 31; ++crush) {
    for (int mod = -63; mod <= 63; mod += 63) {
      native_vc::Reset();
      Set(offsetof(Patch, mix_crush), crush);
      Route(0, MOD_SRC_CONSTANT_256, MOD_DST_MIX_CRUSH, mod);
      Sustain(60, 127);
      CHECK_MSG(voice.crush() >= 1 && voice.crush() <= 64, "crush %d mod %d: %d",
                crush, mod, voice.crush());
    }
  }
}

TEST(SvfFullScaleMixDoesNotWrap) {
  // Sine + triangle sub at full level, balance swept: smooth waveforms, so
  // a sample-to-sample jump near full scale could only be an 8-bit wrap.
  for (int balance = 0; balance <= 63; balance += 21) {
    native_vc::Reset();
    Set(offsetof(Patch, osc[0].shape), WAVEFORM_SINE);
    Set(offsetof(Patch, osc[1].shape), WAVEFORM_TRIANGLE);
    Set(offsetof(Patch, mix_balance), balance);
    Set(offsetof(Patch, mix_sub_osc_shape), WAVEFORM_SUB_OSC_TRIANGLE_1);
    Set(offsetof(Patch, mix_sub_osc), 63);
    Set(offsetof(Patch, modulation[10].amount), 63);
    Sustain(36, 127);
    std::vector<uint8_t> audio;
    native_vc::Render(200, &audio);
    int max_jump = 0;
    for (size_t i = 1; i < audio.size(); ++i) {
      int d = abs(audio[i] - audio[i - 1]);
      if (d > max_jump) max_jump = d;
    }
    CHECK_MSG(max_jump < 64, "balance %d: jump %d", balance, max_jump);
    int p2p = native_vc::PeakToPeak(audio, 0, audio.size());
    // Sine and triangle partly cancel at some balances: only check that
    // there is signal.
    CHECK_MSG(p2p > 64, "balance %d: peak-to-peak %d", balance, p2p);
  }
}
