// Lfo (common/lfo.h): basic shapes, loop flag, sample & hold.
#include "test.h"

#include "common/lfo.h"

using namespace ambika;

namespace {
const uint16_t kIncrement = 65536 / 256;  // 256 renders per cycle
}

TEST(LfoRampRisesOncePerCycle) {
  Lfo l;
  l.set_phase(0);
  l.set_phase_increment(kIncrement);
  int loops = 0;
  uint8_t previous = l.Render(LFO_WAVEFORM_RAMP);
  for (int i = 0; i < 1024; ++i) {
    uint8_t v = l.Render(LFO_WAVEFORM_RAMP);
    if (l.looped()) {
      ++loops;
    } else {
      CHECK(v >= previous);
    }
    previous = v;
  }
  CHECK_EQ(loops, 4);
}

TEST(LfoTriangleIsSymmetric) {
  Lfo l;
  l.set_phase(0);
  l.set_phase_increment(kIncrement);
  int lo = 255, hi = 0;
  long sum = 0;
  for (int i = 0; i < 256; ++i) {
    uint8_t v = l.Render(LFO_WAVEFORM_TRIANGLE);
    if (v < lo) lo = v;
    if (v > hi) hi = v;
    sum += v;
  }
  CHECK(lo <= 2);
  CHECK(hi >= 253);
  CHECK_NEAR(sum / 256, 128, 3);
}

TEST(LfoSquareDutyIsHalf) {
  Lfo l;
  l.set_phase(0);
  l.set_phase_increment(kIncrement);
  int high = 0;
  for (int i = 0; i < 256; ++i) {
    uint8_t v = l.Render(LFO_WAVEFORM_SQUARE);
    CHECK(v == 0 || v == 255);
    high += v == 255;
  }
  CHECK_EQ(high, 128);
}

TEST(LfoSampleAndHoldChangesOnlyOnLoop) {
  Lfo l;
  l.set_phase(0);
  l.set_phase_increment(kIncrement);
  uint8_t held = l.Render(LFO_WAVEFORM_S_H);
  int changes = 0;
  for (int i = 0; i < 256 * 8; ++i) {
    uint8_t v = l.Render(LFO_WAVEFORM_S_H);
    if (v != held) {
      CHECK(l.looped());
      ++changes;
    }
    held = v;
  }
  CHECK(changes >= 4);
}

TEST(LfoPhaseResetReportsLoop) {
  Lfo l;
  l.set_phase(30000);
  l.set_phase_increment(kIncrement);
  l.Render(LFO_WAVEFORM_RAMP);
  l.set_phase(0);  // e.g. key sync
  CHECK(l.looped());
}
