// SVF voicecard control paths (voicecard/cv_ramp.h): the CV ramps the ISR
// runs between blocks, and the filter-mode declicker. The ISR side is
// mirrored here (AdvanceRamp once per CV tick, kCvRampSteps per ramp); the
// main-loop side is the firmware code.
#include "test.h"

#include <stdlib.h>
#include <vector>
#include <avr/pgmspace.h>

#include "common/patch.h"
#include "voicecard/cv_ramp.h"

using namespace ambika;

namespace {

int Abs(int x) { return x < 0 ? -x : x; }

// One CV: the ramp, the ISR's steps counter, and the largest change one
// tick may make for the current ramp (its step plus the final remainder).
struct Cv {
  CvRamp ramp;
  uint8_t steps;
  int allowed;
  int max_excess;  // Largest tick change beyond |allowed| (0 = fine).
  Cv(uint16_t v) : steps(0), allowed(0), max_excess(0) {
    ramp.value = ramp.target = v;
    ramp.step = 0;
  }
  void Retarget(uint16_t target) {
    allowed = (Abs(static_cast<int>(target) - ramp.value) >> kCvRampShift) +
        (1 << kCvRampShift);
    RetargetRamp(&ramp, target);
    steps = kCvRampSteps;
  }
  void StartVca(uint16_t target) {
    if (target != ramp.target) {
      allowed = (Abs(static_cast<int>(target) - ramp.value) >> kCvRampShift) +
          (1 << kCvRampShift);
    }
    steps = StartVcaRamp(&ramp, steps, target);
  }
  // One ISR CV tick (voicecard.cc: TIMER2_OVF_vect, every kCvDecimation
  // samples).
  void Tick() {
    if (!steps) return;
    uint16_t before = ramp.value;
    --steps;
    AdvanceRamp(&ramp, steps == 0);
    int change = Abs(static_cast<int>(ramp.value) - before);
    if (change > allowed && change - allowed > max_excess) {
      max_excess = change - allowed;
    }
  }
};

// YAM+ 0.1-0.3: the step came from the previous *target*.
struct OldCv {
  CvRamp ramp;
  uint8_t steps;
  OldCv(uint16_t v) : steps(0) {
    ramp.value = ramp.target = v;
    ramp.step = 0;
  }
  void Retarget(uint16_t target) {
    ramp.step = (static_cast<int32_t>(target) - ramp.target) / kCvRampSteps;
    ramp.target = target;
    steps = kCvRampSteps;
  }
  int Tick() {
    if (!steps) return 0;
    uint16_t before = ramp.value;
    --steps;
    AdvanceRamp(&ramp, steps == 0);
    return Abs(static_cast<int>(ramp.value) - before);
  }
};

}  // namespace

TEST(CvRampLandsOnTargetWithoutPassingIt) {
  const uint16_t edges[] = { 0, 1, 7, 8, 9, 255, 4095, 0x8000, 0xfeff, 0xff00,
                             0xffff };
  std::vector<uint16_t> values(edges, edges + sizeof(edges) / sizeof(edges[0]));
  srand(7);
  for (int i = 0; i < 200; ++i) values.push_back(rand() & 0xffff);
  for (size_t a = 0; a < values.size(); ++a) {
    for (size_t b = 0; b < values.size(); ++b) {
      CvRamp r;
      r.value = r.target = values[a];
      r.step = 0;
      RetargetRamp(&r, values[b]);
      int lo = values[a] < values[b] ? values[a] : values[b];
      int hi = values[a] < values[b] ? values[b] : values[a];
      int previous = values[a];
      for (uint8_t s = kCvRampSteps; s > 0; --s) {
        AdvanceRamp(&r, s == 1);
        CHECK_MSG(r.value >= lo && r.value <= hi, "%d -> %d: %d outside",
                  values[a], values[b], r.value);
        // Monotonic towards the target.
        CHECK(values[b] >= values[a] ? r.value >= previous
                                     : r.value <= previous);
        previous = r.value;
      }
      CHECK_EQ(r.value, values[b]);
    }
  }
}

TEST(CvRampEarlyBlockDoesNotStepTheVca) {
  // A VCA ramp 0 -> 4000 is cut after 3 of its steps by an early block
  // (the main loop catching up) that asks for 2000.
  OldCv old_cv(0);
  Cv cv(0);
  old_cv.Retarget(4000);
  cv.Retarget(4000);
  for (int i = 0; i < 3; ++i) {
    old_cv.Tick();
    cv.Tick();
  }
  old_cv.Retarget(2000);
  cv.Retarget(2000);
  int old_max = 0;
  for (int i = 0; i < kCvRampSteps; ++i) {
    int c = old_cv.Tick();
    if (c > old_max) old_max = c;
    cv.Tick();
  }
  // The old ramp starts from 1500 with the step of 4000 -> 2000 (-250),
  // goes the wrong way to ... then snaps: a step of over 1000 DAC units.
  CHECK_MSG(old_max > 1000, "old max step %d", old_max);
  CHECK_EQ(cv.max_excess, 0);
  CHECK_EQ(cv.ramp.value, 2000);
}

TEST(CvRampUnchangedVcaLetsTheRampFinish) {
  Cv cv(0);
  cv.StartVca(4000);
  cv.Tick();
  cv.Tick();
  cv.StartVca(4000);  // Early block, same level: the ramp keeps going.
  CHECK_EQ(cv.steps, kCvRampSteps - 2);
  while (cv.steps) cv.Tick();
  CHECK_EQ(cv.max_excess, 0);
  CHECK_EQ(cv.ramp.value, 4000);
  // Idle and unchanged: one refresh step per block (the DAC write).
  cv.StartVca(4000);
  CHECK_EQ(cv.steps, 1);
}

TEST(CvRampRandomBlockTimingNeverSteps) {
  // Envelope-like VCA and cutoff paths, with blocks arriving every 1-60
  // samples (catch-up bursts and late blocks): no tick ever moves a CV by
  // more than its ramp's step plus the final remainder.
  srand(11);
  Cv vca(0), cutoff(0x4000);
  int level = 0, freq = 0x4000;
  for (int block = 0; block < 20000; ++block) {
    level += (rand() % 801) - 400;
    level = level < 0 ? 0 : level > 4095 ? 4095 : level;
    freq += (rand() % 8001) - 4000;
    freq = freq < 0 ? 0 : freq > 0xff00 ? 0xff00 : freq;
    vca.StartVca(level);
    if (freq != cutoff.ramp.target) cutoff.Retarget(freq);
    int samples = 1 + rand() % 60;
    for (int s = 0; s < samples; ++s) {
      if (s % kCvDecimation == 0) {
        vca.Tick();
        cutoff.Tick();
      }
    }
  }
  CHECK_EQ(vca.max_excess, 0);
  CHECK_EQ(cutoff.max_excess, 0);
}

TEST(FilterModeFirstBlockAndUnchangedMode) {
  FilterModeDeclicker d;
  uint8_t level = 200;
  CHECK_EQ(d.Update(FILTER_MODE_HP, &level, 0), FILTER_MODE_HP);  // At boot.
  CHECK_EQ(level, 200);
  CHECK_EQ(d.Update(FILTER_MODE_HP, &level, 0), 0xff);
  CHECK_EQ(level, 200);
}

TEST(FilterModeChangeWaitsForSilence) {
  FilterModeDeclicker d;
  uint8_t level = 180;
  d.Update(FILTER_MODE_LP, &level, 1);
  // The user picks BP while the note sounds: the VCA is pulled to 0 first.
  level = 180;
  CHECK_EQ(d.Update(FILTER_MODE_BP, &level, 1), 0xff);
  CHECK_EQ(level, 0);
  // Next block, but the ISR hasn't finished the ramp down yet: still wait.
  level = 180;
  CHECK_EQ(d.Update(FILTER_MODE_BP, &level, 0), 0xff);
  CHECK_EQ(level, 0);
  // Ramp done: switch, and the level comes back.
  level = 180;
  CHECK_EQ(d.Update(FILTER_MODE_BP, &level, 1), FILTER_MODE_BP);
  CHECK_EQ(level, 180);
  CHECK_EQ(d.current(), FILTER_MODE_BP);
}

TEST(FilterModeChangeOnSilentVoiceIsImmediate) {
  FilterModeDeclicker d;
  uint8_t level = 0;
  d.Update(FILTER_MODE_LP, &level, 1);
  level = 0;
  d.Update(FILTER_MODE_LP, &level, 1);  // Released and decayed.
  level = 0;
  CHECK_EQ(d.Update(FILTER_MODE_NOTCH, &level, 1), FILTER_MODE_NOTCH);
  // A note starting in the same block as the change: the mode is already
  // right, so nothing holds it back.
  level = 0;
  d.Update(FILTER_MODE_NOTCH, &level, 1);
  level = 90;
  CHECK_EQ(d.Update(FILTER_MODE_LP, &level, 1), FILTER_MODE_LP);
  CHECK_EQ(level, 90);
}

TEST(FilterModeIsMaskedToTheFourOutputs) {
  // YAM read filter_mode_bytes[mode] (4 bytes of RAM) and wrote the result
  // unmasked to PORTC: a corrupt mode byte selected unused mux inputs and
  // touched the port's other pins.
  for (int mode = 0; mode < 256; ++mode) {
    FilterModeDeclicker d;
    uint8_t level = 0;
    uint8_t written = d.Update(mode, &level, 1);
    CHECK_EQ(written, mode & 3);
  }
}

TEST(FilterModeSwitchHappensAtVcaSilence) {
  // Whole chain at block rate with the ISR mirrored: a sounding voice, a
  // mode change, and the DAC level at the moment the mode port is written.
  FilterModeDeclicker d;
  Cv vca(0);
  uint8_t level = 200;
  d.Update(FILTER_MODE_LP, &level, 1);
  int written_at_level = -1;
  for (int block = 0; block < 12; ++block) {
    level = 200;
    uint8_t requested = block >= 4 ? FILTER_MODE_HP : FILTER_MODE_LP;
    uint8_t mode = d.Update(requested, &level, vca.steps == 0);
    if (mode != 0xff) written_at_level = vca.ramp.value;
    vca.StartVca(level * 16);
    for (int s = 0; s < 40; ++s) {
      if (s % kCvDecimation == 0) vca.Tick();
    }
  }
  CHECK_EQ(written_at_level, 0);
  CHECK_EQ(d.current(), FILTER_MODE_HP);
  CHECK_EQ(vca.ramp.value, 200 * 16);  // Back to full level.
  CHECK_EQ(vca.max_excess, 0);
}
