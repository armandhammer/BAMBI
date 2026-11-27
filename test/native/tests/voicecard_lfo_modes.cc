// BAMBI voice LFO trigger modes (free / retrigger / one-shot), voice LFO
// slew, and the velocity curve, through the real Voice code.
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

const uint8_t kRate = 90;  // A cycle of a few dozen blocks.

uint16_t Note(uint8_t midi_note) { return midi_note << 7; }

uint8_t LfoOut() { return voice.modulation_source(MOD_SRC_LFO_4); }

void SetupLfo(uint8_t shape, uint8_t mode, uint8_t slew) {
  native_vc::Reset();
  native_vc::SetPatch(PRM_PATCH_VOICE_LFO_SHAPE, shape);
  native_vc::SetPatch(PRM_PATCH_VOICE_LFO_RATE, kRate);
  native_vc::SetPatch(PRM_PATCH_VOICE_LFO_MODE, mode);
  native_vc::SetPatch(PRM_PATCH_VOICE_LFO_SLEW, slew);
  native_vc::Render(1);  // Latches the rate.
}

// LFO_4 values of the next |blocks| blocks.
std::vector<uint8_t> Trace(int blocks) {
  std::vector<uint8_t> v;
  for (int i = 0; i < blocks; ++i) {
    native_vc::Render(1);
    v.push_back(LfoOut());
  }
  return v;
}

// Blocks per cycle of the ramp at kRate, measured on a free-running LFO.
int CycleLength() {
  SetupLfo(LFO_WAVEFORM_RAMP, VOICE_LFO_MODE_FREE, 0);
  std::vector<uint8_t> v = Trace(400);
  int first = -1;
  for (size_t i = 1; i < v.size(); ++i) {
    if (v[i] < v[i - 1]) {
      if (first < 0) {
        first = i;
      } else {
        return i - first;
      }
    }
  }
  return -1;
}

}  // namespace

TEST(VoiceLfoPatchLayout) {
  CHECK_EQ(offsetof(Patch, voice_lfo_mode), PRM_PATCH_VOICE_LFO_MODE);
  CHECK_EQ(offsetof(Patch, voice_lfo_slew), PRM_PATCH_VOICE_LFO_SLEW);
  CHECK_EQ(offsetof(Patch, env_lfo[0].padding), PRM_PATCH_VELOCITY_CURVE);
  CHECK_EQ(sizeof(Patch), 112);
}

TEST(VoiceLfoCycleIsUsableForTheseTests) {
  int n = CycleLength();
  CHECK(n >= 20 && n <= 200);
}

TEST(VoiceLfoFreeModeIgnoresNotes) {
  // Stock behaviour: a note in the middle of the ramp doesn't send it back
  // to the bottom.
  int n = CycleLength();
  SetupLfo(LFO_WAVEFORM_RAMP, VOICE_LFO_MODE_FREE, 0);
  for (int k = 0; k < 4; ++k) {
    int guard = 0;
    while ((LfoOut() < 80 + 30 * k || LfoOut() > 110 + 30 * k) &&
           guard++ < 4 * n) {
      native_vc::Render(1);
    }
    uint8_t before = LfoOut();
    voice.Trigger(Note(60 + k), 127, 0);
    native_vc::Render(1);
    CHECK_MSG(LfoOut() > before, "note %d: %d -> %d", k, before, LfoOut());
  }
}

TEST(VoiceLfoRetriggerRestartsTheCycle) {
  int n = CycleLength();
  // Trigger at two different phases: the traces after the note match, and
  // start at the bottom of the ramp.
  SetupLfo(LFO_WAVEFORM_RAMP, VOICE_LFO_MODE_RETRIGGER, 0);
  Trace(7);
  voice.Trigger(Note(60), 127, 0);
  std::vector<uint8_t> a = Trace(2 * n);
  SetupLfo(LFO_WAVEFORM_RAMP, VOICE_LFO_MODE_RETRIGGER, 0);
  Trace(n / 2 + 3);
  voice.Trigger(Note(64), 100, 0);
  std::vector<uint8_t> b = Trace(2 * n);
  CHECK(a == b);
  CHECK(a[0] < 256 / n + 2);
  // Keeps running after the first cycle.
  CHECK(a[n + 2] < a[n + n / 2]);
}

TEST(VoiceLfoRetriggerIgnoresLegatoNotes) {
  int n = CycleLength();
  SetupLfo(LFO_WAVEFORM_RAMP, VOICE_LFO_MODE_RETRIGGER, 0);
  native_vc::SetPart(5, 1);  // Part::legato
  voice.Trigger(Note(60), 127, 0);
  Trace(n / 2);
  uint8_t before = LfoOut();
  voice.Trigger(Note(62), 127, 1);  // Legato: no restart.
  native_vc::Render(1);
  CHECK(LfoOut() > before);
  voice.Trigger(Note(64), 127, 0);  // Non-legato: restart.
  native_vc::Render(1);
  CHECK(LfoOut() < before);
}

TEST(VoiceLfoOneShotRunsOneCycleThenHolds) {
  int n = CycleLength();
  SetupLfo(LFO_WAVEFORM_RAMP, VOICE_LFO_MODE_ONE_SHOT, 0);
  Trace(13);
  voice.Trigger(Note(60), 127, 0);
  std::vector<uint8_t> v = Trace(5 * n);
  // Rises through one cycle...
  for (int i = 1; i < n - 1; ++i) {
    CHECK_MSG(v[i] >= v[i - 1], "block %d: %d < %d", i, v[i], v[i - 1]);
  }
  // ...then holds near the top of the ramp, never wrapping to the bottom.
  uint8_t hold = v[n + 1];
  CHECK(hold >= 255 - 256 / n - 2);
  for (int i = n + 1; i < 5 * n; ++i) {
    CHECK_EQ(v[i], hold);
  }
  // The next note restarts it.
  voice.Trigger(Note(62), 127, 0);
  native_vc::Render(1);
  CHECK(LfoOut() < 256 / n + 2);
}

TEST(VoiceLfoOneShotSquareAndTriangleEndHigh) {
  int n = CycleLength();
  const uint8_t shapes[] = { LFO_WAVEFORM_SQUARE, LFO_WAVEFORM_TRIANGLE };
  for (int s = 0; s < 2; ++s) {
    SetupLfo(shapes[s], VOICE_LFO_MODE_ONE_SHOT, 0);
    voice.Trigger(Note(60), 127, 0);
    std::vector<uint8_t> v = Trace(3 * n);
    CHECK_MSG(v[3 * n - 1] >= 240, "shape %d holds %d", shapes[s],
              v[3 * n - 1]);
    CHECK_EQ(v[2 * n], v[3 * n - 1]);
  }
}

TEST(VoiceLfoOneShotSampleAndHoldIsOneValuePerNote) {
  int n = CycleLength();
  SetupLfo(LFO_WAVEFORM_S_H, VOICE_LFO_MODE_ONE_SHOT, 0);
  std::vector<uint8_t> per_note;
  for (int note = 0; note < 8; ++note) {
    voice.Trigger(Note(60 + note), 127, 0);
    std::vector<uint8_t> v = Trace(4 * n);
    for (size_t i = 1; i < v.size(); ++i) {
      CHECK_MSG(v[i] == v[0], "note %d changed at block %d", note, (int)i);
    }
    per_note.push_back(v[0]);
  }
  int distinct = 0;
  for (size_t i = 1; i < per_note.size(); ++i) {
    distinct += per_note[i] != per_note[i - 1];
  }
  CHECK(distinct >= 5);
}

TEST(VoiceLfoRetriggerDrawsNewSampleAndHoldValue) {
  SetupLfo(LFO_WAVEFORM_S_H, VOICE_LFO_MODE_RETRIGGER, 0);
  int changes = 0;
  uint8_t previous = LfoOut();
  for (int note = 0; note < 8; ++note) {
    voice.Trigger(Note(60), 127, 0);
    native_vc::Render(1);
    changes += LfoOut() != previous;
    previous = LfoOut();
  }
  CHECK(changes >= 6);
}

TEST(VoiceLfoSlewZeroIsUnchanged) {
  SetupLfo(LFO_WAVEFORM_SQUARE, VOICE_LFO_MODE_FREE, 0);
  std::vector<uint8_t> v = Trace(400);
  for (size_t i = 0; i < v.size(); ++i) {
    CHECK(v[i] == 0 || v[i] == 255);
  }
}

TEST(VoiceLfoSlewSmoothsStepsWithoutOvershoot) {
  // A square wave through the slew: bounded per-block change, values stay
  // between the two levels, and the output still swings most of the way.
  SetupLfo(LFO_WAVEFORM_SQUARE, VOICE_LFO_MODE_FREE, 8);
  std::vector<uint8_t> v = Trace(800);
  int max_step = 0, lo = 255, hi = 0;
  for (size_t i = 1; i < v.size(); ++i) {
    int d = abs(v[i] - v[i - 1]);
    if (d > max_step) max_step = d;
    if (v[i] < lo) lo = v[i];
    if (v[i] > hi) hi = v[i];
  }
  CHECK_MSG(max_step <= 64, "max step %d", max_step);
  CHECK(max_step > 0);
  CHECK(hi - lo >= 128);
}

TEST(VoiceLfoMoreSlewIsSmoother) {
  int previous = 256;
  const uint8_t slews[] = { 1, 20, 40, 60, 80 };
  for (int s = 0; s < 5; ++s) {
    SetupLfo(LFO_WAVEFORM_SQUARE, VOICE_LFO_MODE_FREE, slews[s]);
    std::vector<uint8_t> v = Trace(600);
    int max_step = 0;
    for (size_t i = 1; i < v.size(); ++i) {
      int d = abs(v[i] - v[i - 1]);
      if (d > max_step) max_step = d;
    }
    CHECK_MSG(max_step <= previous, "slew %d: step %d > %d", slews[s],
              max_step, previous);
    previous = max_step;
  }
  CHECK(previous < 16);
}

TEST(VoiceLfoSlewConvergesExactly) {
  // One-shot square holds 255: even the slowest coefficients must land on
  // it exactly (the step is never rounded to zero).
  const uint8_t slews[] = { 1, 64, 100 };
  for (int s = 0; s < 3; ++s) {
    SetupLfo(LFO_WAVEFORM_SQUARE, VOICE_LFO_MODE_ONE_SHOT, slews[s]);
    voice.Trigger(Note(60), 127, 0);
    native_vc::Render(30000);
    CHECK_MSG(LfoOut() == 255, "slew %d: %d", slews[s], LfoOut());
  }
}

TEST(VoiceLfoSlewedSampleAndHoldGlides) {
  // "S&H slew": each new random value is approached gradually.
  SetupLfo(LFO_WAVEFORM_S_H, VOICE_LFO_MODE_FREE, 30);
  std::vector<uint8_t> v = Trace(2000);
  int max_step = 0, distinct = 0;
  for (size_t i = 1; i < v.size(); ++i) {
    int d = abs(v[i] - v[i - 1]);
    if (d > max_step) max_step = d;
    distinct += d != 0;
  }
  CHECK(max_step < 48);
  CHECK(distinct > 200);  // Moving most of the time, not stepping.
}

TEST(VelocityCurveShapes) {
  native_vc::Reset();
  for (int curve = 0; curve < VELOCITY_CURVE_LAST; ++curve) {
    native_vc::SetPatch(PRM_PATCH_VELOCITY_CURVE, curve);
    int previous = -1;
    for (int v = 0; v < 256; ++v) {
      int out = voice.ApplyVelocityCurve(v);
      CHECK_MSG(out >= previous, "curve %d not monotonic at %d", curve, v);
      previous = out;
      if (curve == VELOCITY_CURVE_LINEAR) CHECK_EQ(out, v);
      if (curve == VELOCITY_CURVE_SOFT) CHECK(out >= v);
      if (curve == VELOCITY_CURVE_HARD) CHECK(out <= v);
    }
    CHECK_EQ(voice.ApplyVelocityCurve(0), 0);
    CHECK_EQ(voice.ApplyVelocityCurve(255), 255);
    CHECK(voice.ApplyVelocityCurve(254) >= 252);  // MIDI 127 << 1
  }
  native_vc::SetPatch(PRM_PATCH_VELOCITY_CURVE, VELOCITY_CURVE_SOFT);
  CHECK_NEAR(voice.ApplyVelocityCurve(128), 192, 2);
  native_vc::SetPatch(PRM_PATCH_VELOCITY_CURVE, VELOCITY_CURVE_HARD);
  CHECK_NEAR(voice.ApplyVelocityCurve(128), 64, 2);
  // Soft and hard mirror each other.
  for (int v = 0; v < 256; ++v) {
    native_vc::SetPatch(PRM_PATCH_VELOCITY_CURVE, VELOCITY_CURVE_SOFT);
    int soft = voice.ApplyVelocityCurve(v);
    native_vc::SetPatch(PRM_PATCH_VELOCITY_CURVE, VELOCITY_CURVE_HARD);
    int hard = voice.ApplyVelocityCurve(255 - v);
    CHECK_EQ(soft, 255 - hard);
  }
  // An out-of-range byte (unsanitized dump) behaves as linear.
  native_vc::SetPatch(PRM_PATCH_VELOCITY_CURVE, 77);
  CHECK_EQ(voice.ApplyVelocityCurve(100), 100);
}

TEST(VelocityCurveAppliesToTheVelocitySource) {
  const uint8_t expected_order[] = {
    VELOCITY_CURVE_HARD, VELOCITY_CURVE_LINEAR, VELOCITY_CURVE_SOFT };
  int previous = -1;
  for (int i = 0; i < 3; ++i) {
    native_vc::Reset();
    native_vc::SetPatch(PRM_PATCH_VELOCITY_CURVE, expected_order[i]);
    voice.Trigger(Note(60), 80, 0);  // MIDI velocity 40
    native_vc::Render(1);
    int v = voice.modulation_source(MOD_SRC_VELOCITY);
    CHECK_EQ(v, voice.ApplyVelocityCurve(80));
    CHECK(v > previous);
    previous = v;
  }
}

TEST(VelocityCurveChangesVelocityToVcaLevel) {
  // Default routing 11 is velocity -> VCA (amount 0): open it fully and
  // compare the VCA level of a medium-soft note under each curve.
  int vca[VELOCITY_CURVE_LAST];
  for (int curve = 0; curve < VELOCITY_CURVE_LAST; ++curve) {
    native_vc::Reset();
    native_vc::SetPatch(offsetof(Patch, osc[0].shape), WAVEFORM_POLYBLEP_SAW);
    native_vc::SetPatch(offsetof(Patch, modulation[10].amount), 63);
    native_vc::SetPatch(offsetof(Patch, modulation[11].amount), 63);
    for (uint8_t e = 0; e < 3; ++e) {
      uint8_t base = offsetof(Patch, env_lfo) + e * sizeof(EnvelopeLfoSettings);
      native_vc::SetPatch(base + offsetof(EnvelopeLfoSettings, attack), 0);
      native_vc::SetPatch(base + offsetof(EnvelopeLfoSettings, sustain), 127);
    }
    native_vc::SetPatch(PRM_PATCH_VELOCITY_CURVE, curve);
    native_vc::Render(1);
    voice.Trigger(Note(60), 80, 0);
    native_vc::Render(200);
    vca[curve] = voice.vca();
  }
  CHECK_MSG(vca[VELOCITY_CURVE_HARD] < vca[VELOCITY_CURVE_LINEAR] &&
            vca[VELOCITY_CURVE_LINEAR] < vca[VELOCITY_CURVE_SOFT],
            "vca hard %d linear %d soft %d", vca[VELOCITY_CURVE_HARD],
            vca[VELOCITY_CURVE_LINEAR], vca[VELOCITY_CURVE_SOFT]);
}
