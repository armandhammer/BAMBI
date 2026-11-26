// Envelope (voicecard/envelope.h) including the YAM+ segment curves
// (NRPN 106-108): 0 = stock exponential, 64 = linear, 127 = inverse.
#include "test.h"

#include <vector>

#include "voicecard/envelope.h"

using namespace ambika;

namespace {

// Renders one envelope from trigger through |hold| steps of gate, then
// release until DEAD (or a step limit). Returns every output value.
std::vector<uint8_t> RunEnvelope(uint8_t a, uint8_t d, uint8_t s, uint8_t r,
                                 uint8_t curve, int hold,
                                 std::vector<uint8_t>* stages = 0) {
  Envelope e;
  e.Init();
  e.Update(a, d, s, r, curve);
  e.Trigger(DEAD);
  e.Trigger(ATTACK);
  std::vector<uint8_t> out;
  for (int i = 0; i < hold; ++i) {
    out.push_back(e.Render());
    if (stages) stages->push_back(e.stage());
  }
  e.Trigger(RELEASE);
  for (int i = 0; i < 200000 && e.stage() != DEAD; ++i) {
    out.push_back(e.Render());
    if (stages) stages->push_back(e.stage());
  }
  return out;
}

// Value at the middle of the attack segment, by step count.
int AttackMidpoint(uint8_t curve) {
  std::vector<uint8_t> stages;
  std::vector<uint8_t> v = RunEnvelope(70, 70, 64, 70, curve, 20000, &stages);
  size_t attack_steps = 0;
  while (attack_steps < stages.size() && stages[attack_steps] == ATTACK) {
    ++attack_steps;
  }
  return v[attack_steps / 2];
}

}  // namespace

TEST(EnvelopeReachesPeakSustainAndZero) {
  std::vector<uint8_t> stages;
  std::vector<uint8_t> v = RunEnvelope(40, 40, 64, 40, 0, 30000, &stages);
  uint8_t peak = 0;
  for (size_t i = 0; i < v.size(); ++i) {
    if (v[i] > peak) peak = v[i];
  }
  // The C fallback of U8MixU16 tops out at 254; the first decay step
  // follows the attack's last one.
  CHECK(peak >= 245);
  // Held long enough: sitting at sustain (64 << 1 = 128).
  CHECK_EQ(stages[29999], SUSTAIN);
  CHECK_NEAR(v[29999], 128, 2);
  CHECK_EQ(v.back(), 0);
}

TEST(EnvelopeSegmentsAreMonotonicForEveryCurve) {
  for (int curve = 0; curve <= 127; ++curve) {
    std::vector<uint8_t> stages;
    std::vector<uint8_t> v = RunEnvelope(50, 50, 40, 50, curve, 20000,
                                         &stages);
    for (size_t i = 1; i < v.size(); ++i) {
      if (stages[i] != stages[i - 1]) continue;
      if (stages[i] == ATTACK) {
        CHECK_MSG(v[i] >= v[i - 1], "curve %d: attack fell %d -> %d at %d",
                  curve, v[i - 1], v[i], (int)i);
      } else if (stages[i] == DECAY || stages[i] == RELEASE) {
        CHECK_MSG(v[i] <= v[i - 1], "curve %d: stage %d rose %d -> %d at %d",
                  curve, stages[i], v[i - 1], v[i], (int)i);
      }
    }
  }
}

TEST(EnvelopeCurveLinearIsLinear) {
  CHECK_NEAR(AttackMidpoint(64), 128, 6);
}

TEST(EnvelopeCurveStockIsFastStart) {
  // Stock YAM segments are exponential: most of the rise happens early.
  CHECK(AttackMidpoint(0) > 160);
}

TEST(EnvelopeCurveInverseIsSlowStart) {
  CHECK(AttackMidpoint(127) < 96);
}

TEST(EnvelopeCurveMidpointMovesSteadily) {
  // Turning the curve knob from 0 to 127 must sweep the shape from fast to
  // slow start without jumps back.
  int previous = 256;
  for (int curve = 0; curve <= 127; curve += 8) {
    int mid = AttackMidpoint(curve);
    CHECK_MSG(mid <= previous + 2, "curve %d midpoint %d after %d", curve,
              mid, previous);
    previous = mid;
  }
}

TEST(EnvelopeSegmentDurationDoesNotDependOnCurve) {
  // The curve reshapes a segment but must not change how long it lasts.
  size_t reference = 0;
  for (int curve = 0; curve <= 127; curve += 21) {
    std::vector<uint8_t> stages;
    RunEnvelope(60, 60, 64, 60, curve, 20000, &stages);
    size_t n = 0;
    while (n < stages.size() && stages[n] == ATTACK) ++n;
    if (!reference) reference = n;
    CHECK_NEAR(n, reference, 1);
  }
}

TEST(EnvelopeRetriggerFromCurrentLevel) {
  // Re-triggering mid-release starts the attack from where the envelope is,
  // not from 0 (no click).
  Envelope e;
  e.Init();
  e.Update(60, 60, 100, 60, 0);
  e.Trigger(ATTACK);
  for (int i = 0; i < 20000; ++i) e.Render();
  e.Trigger(RELEASE);
  uint8_t level = 0;
  for (int i = 0; i < 300; ++i) level = e.Render();
  CHECK(level > 20);
  e.Trigger(ATTACK);
  uint8_t first = e.Render();
  CHECK_NEAR(first, level, 3);
}

TEST(EnvelopeFastestSettingsDoNotOverflow) {
  for (int curve = 0; curve <= 127; curve += 127) {
    std::vector<uint8_t> v = RunEnvelope(0, 0, 127, 0, curve, 100);
    CHECK(v.size() < 1000);
    CHECK_EQ(v.back(), 0);
  }
}
