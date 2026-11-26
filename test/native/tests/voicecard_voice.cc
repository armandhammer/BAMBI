// Headless voice rendering: the full voicecard DSP path (modulation matrix,
// oscillators, mixer, envelopes, YAM+ vintage) without the hardware.
#include "test.h"
#include "voicecard_env.h"

#include <stddef.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <vector>

#include "common/patch.h"
#include "voicecard/voice.h"

using namespace ambika;

namespace {

uint16_t Note(uint8_t midi_note) { return midi_note << 7; }

// A playable patch: osc 1 saw only, filter open, env 2 -> VCA at full depth
// (default routing), quick attack, full sustain. Call after Reset(); the
// envelope times apply from the next block.
void BasicPatch() {
  native_vc::SetPatch(offsetof(Patch, osc[0].shape), WAVEFORM_POLYBLEP_SAW);
  native_vc::SetPatch(offsetof(Patch, mix_balance), 0);
  native_vc::SetPatch(offsetof(Patch, filter[0].cutoff), 127);
  for (uint8_t e = 0; e < 3; ++e) {
    uint8_t base = offsetof(Patch, env_lfo) + e * sizeof(EnvelopeLfoSettings);
    native_vc::SetPatch(base + offsetof(EnvelopeLfoSettings, attack), 10);
    native_vc::SetPatch(base + offsetof(EnvelopeLfoSettings, sustain), 127);
    native_vc::SetPatch(base + offsetof(EnvelopeLfoSettings, release), 30);
  }
  native_vc::SetPatch(offsetof(Patch, modulation[10].amount), 63);
  native_vc::Render(1);
}

uint8_t R(int n) { return rand() % n; }

// Random but in-range value for every patch field (the ranges the
// controller's parameter table allows).
void RandomPatch() {
  Patch p;
  uint8_t* b = reinterpret_cast<uint8_t*>(&p);
  for (size_t i = 0; i < sizeof(p); ++i) b[i] = R(128);
  for (int i = 0; i < kNumOscillators; ++i) {
    p.osc[i].shape = R(WAVEFORM_LAST);
    p.osc[i].range = R(49) - 24;
    p.osc[i].detune = R(128) - 64;
  }
  p.mix_balance = R(64);
  p.mix_op = R(OP_LAST);
  p.mix_parameter = R(64);
  p.mix_sub_osc_shape = R(WAVEFORM_SUB_OSC_LAST);
  p.mix_sub_osc = R(64);
  p.mix_noise = R(64);
  p.mix_fuzz = R(64);
  p.mix_crush = R(32);
  for (int i = 0; i < 2; ++i) {
    p.filter[i].resonance = R(64);
    p.filter[i].mode = R(4);
  }
  p.filter_env = R(128) - 64;
  p.filter_lfo = R(128) - 64;
  for (int i = 0; i < kNumEnvelopes; ++i) {
    p.env_lfo[i].shape = R(LFO_WAVEFORM_LAST);
    p.env_lfo[i].retrigger_mode = R(LFO_SYNC_MODE_LAST);
  }
  p.voice_lfo_shape = R(LFO_WAVEFORM_LAST);
  for (int i = 0; i < kNumModulations; ++i) {
    p.modulation[i].source = R(MOD_SRC_LAST);
    p.modulation[i].destination = R(MOD_DST_LAST);
    p.modulation[i].amount = R(128) - 64;
  }
  for (int i = 0; i < kNumModifiers; ++i) {
    p.modifier[i].operands[0] = R(MOD_SRC_LAST);
    p.modifier[i].operands[1] = R(MOD_SRC_LAST);
    p.modifier[i].op = R(MODIFIER_LAST);
  }
  p.filter_velo = R(128) - 64;
  p.filter_kbt = R(128) - 64;
  for (size_t i = 0; i < sizeof(p); ++i) native_vc::SetPatch(i, b[i]);
}

// Patch byte offsets (common/patch.h).
const uint8_t kPatchSize = sizeof(Patch);
const uint8_t kOffsetVintage = 109;
const uint8_t kOffsetEnvCurve = 106;

}  // namespace

TEST(VoiceSetPatchWritesThePatch) {
  // Stock YAM wrote patch bytes through patch_data_[address + 1] and relied
  // on the linker placing patch_ right after that 1-byte array (true for
  // avr-gcc 4.3.5, false for host g++). BAMBI writes patch_ directly.
  native_vc::Reset();
  native_vc::SetPatch(kOffsetVintage, 99);
  CHECK_EQ(voice.patch().vintage, 99);
  native_vc::SetPatch(0, 3);
  CHECK_EQ(voice.patch().osc[0].shape, 3);
  CHECK(voice.mutable_patch_data() ==
        reinterpret_cast<const uint8_t*>(&voice.patch()));
}

TEST(VoicePatchLayoutMatchesProtocol) {
  CHECK_EQ(kPatchSize, 112);
  CHECK_EQ(offsetof(Patch, env_curve), kOffsetEnvCurve);
  CHECK_EQ(offsetof(Patch, vintage), kOffsetVintage);
}

TEST(VoiceSilentUntilTriggered) {
  native_vc::Reset();
  std::vector<uint8_t> audio;
  native_vc::Render(50, &audio);
  CHECK_EQ(native_vc::PeakToPeak(audio, 0, audio.size()), 0);
}

TEST(VoiceNoteProducesSoundThenDecaysAfterRelease) {
  native_vc::Reset();
  BasicPatch();
  voice.Trigger(Note(60), 127, 0);
  std::vector<uint8_t> audio;
  std::vector<uint8_t> vca;
  native_vc::Render(200, &audio, 0, &vca);
  CHECK(native_vc::PeakToPeak(audio, audio.size() - 400, 400) > 64);
  CHECK(vca.back() > 100);
  voice.Release();
  vca.clear();
  native_vc::Render(4000, 0, 0, &vca);
  CHECK_MSG(vca.back() < 2, "VCA still at %d after release", vca.back());
}

TEST(VoiceOutputPitchFollowsNote) {
  // Count rising zero crossings of the default saw over a fixed time; one
  // octave up must double them.
  int crossings[2];
  for (int k = 0; k < 2; ++k) {
    native_vc::Reset();
    BasicPatch();
    voice.Trigger(Note(48 + 12 * k), 127, 0);
    std::vector<uint8_t> audio;
    native_vc::Render(500, &audio);
    int n = 0;
    for (size_t i = 8000; i + 1 < audio.size(); ++i) {
      n += audio[i] < 128 && audio[i + 1] >= 128;
    }
    crossings[k] = n;
  }
  CHECK(crossings[0] > 10);
  CHECK_NEAR(crossings[1], crossings[0] * 2, crossings[0] / 8 + 2);
}

TEST(VoiceVintageZeroIsIdenticalAcrossSlots) {
  // With vintage off, every slot computes the same control signals.
  // (Audio differs: oscillator phases carry over from earlier tests.)
  std::vector<uint16_t> ref_cutoff;
  std::vector<uint8_t> ref_vca;
  for (uint8_t slot = 0; slot < 6; ++slot) {
    native_vc::Reset(slot);
    BasicPatch();
    voice.Trigger(Note(57), 100, 0);
    std::vector<uint16_t> cutoff;
    std::vector<uint8_t> vca;
    native_vc::Render(100, 0, &cutoff, &vca);
    if (slot == 0) {
      ref_cutoff = cutoff;
      ref_vca = vca;
    } else {
      CHECK_MSG(cutoff == ref_cutoff, "slot %d cutoff differs", slot);
      CHECK_MSG(vca == ref_vca, "slot %d VCA differs", slot);
    }
  }
}

TEST(VoiceVintageGivesEachSlotItsOwnCutoff) {
  std::vector<uint16_t> cutoffs;
  for (uint8_t slot = 0; slot < 6; ++slot) {
    native_vc::Reset(slot);
    BasicPatch();
    native_vc::SetPatch(kOffsetVintage, 127);
    voice.Trigger(Note(57), 100, 0);
    std::vector<uint16_t> cutoff;
    native_vc::Render(50, 0, &cutoff);
    cutoffs.push_back(cutoff.back());
  }
  int distinct = 0;
  for (size_t i = 0; i < cutoffs.size(); ++i) {
    bool seen = false;
    for (size_t j = 0; j < i; ++j) seen |= cutoffs[j] == cutoffs[i];
    distinct += !seen;
  }
  CHECK_MSG(distinct >= 4, "only %d distinct cutoffs across 6 slots", distinct);
}

TEST(VoiceRandomPatchesNeverCrash) {
  // Fuzz: random in-range values in every patch field, random notes, many
  // blocks. Catches table reads past the end (run with SANITIZE=1) and
  // crashes in the oscillator/modulation code.
  srand(1);
  for (int round = 0; round < 500; ++round) {
    native_vc::Reset(round % 6);
    RandomPatch();
    voice.Trigger(Note(R(128)), R(128), 0);
    native_vc::Render(20);
    voice.Release();
    native_vc::Render(5);
  }
  CHECK(1);
}
