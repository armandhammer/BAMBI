// End-to-end through the headless controller: boot, MIDI notes in,
// voicecard commands out.
#include "test.h"
#include "controller_env.h"

#include "common/protocol.h"
#include "controller/multi.h"

using namespace ambika;

namespace {

// Finds a NOTE_ON (0x10/0x11) command followed by pitch MSB/LSB and
// velocity in a voicecard stream. Pitch is in 1/128 semitone. Returns the
// nearest MIDI note, or -1.
int FindNoteOn(const std::vector<uint8_t>& bytes, uint8_t* velocity) {
  for (size_t i = 0; i + 3 < bytes.size(); ++i) {
    if (bytes[i] == COMMAND_NOTE_ON || bytes[i] == COMMAND_NOTE_ON_LEGATO) {
      if (velocity) *velocity = bytes[i + 3];
      uint16_t pitch = (bytes[i + 1] << 8) | bytes[i + 2];
      return (pitch + 64) >> 7;
    }
  }
  return -1;
}

uint8_t PopCount(uint8_t x) {
  uint8_t n = 0;
  for (; x; x >>= 1) n += x & 1;
  return n;
}

int CountByte(const std::vector<uint8_t>& bytes, uint8_t value) {
  int n = 0;
  for (size_t i = 0; i < bytes.size(); ++i) n += bytes[i] == value;
  return n;
}

}  // namespace

TEST(BootLoadsDefaultMulti) {
  native_env::Boot();
  // Factory multi: part 1 on channel 1 with all six voices.
  CHECK_EQ(multi.data().part_mapping_[0].midi_channel, 1);
  // voice_allocation is a bitmask of voicecards; parts must not overlap.
  uint8_t all = 0;
  for (uint8_t i = 0; i < kNumParts; ++i) {
    uint8_t mask = multi.data().part_mapping_[i].voice_allocation;
    CHECK_EQ(all & mask, 0);
    all |= mask;
  }
  CHECK(all <= 0x3f);
  CHECK(multi.data().part_mapping_[0].voice_allocation != 0);
}

TEST(BootNoteOnReachesAVoicecard) {
  native_env::Boot();
  native_env::MidiIn3(0x90, 60, 100);
  native_env::Run(4);
  int found = 0;
  for (uint8_t v = 0; v < kNumVoices; ++v) {
    uint8_t velocity = 0;
    int note = FindNoteOn(native_env::VoicecardBytes(v), &velocity);
    if (note >= 0) {
      ++found;
      // Pitch is sent in 1/128 semitone (MSB = semitone); allow detune.
      CHECK_NEAR(note, 60, 1);
      CHECK_EQ(velocity, 100 << 1);
    }
  }
  CHECK_EQ(found, 1);
}

TEST(BootNoteOffReleasesTheVoice) {
  native_env::Boot();
  native_env::MidiIn3(0x90, 60, 100);
  native_env::Run(4);
  int voice = -1;
  for (uint8_t v = 0; v < kNumVoices; ++v) {
    if (FindNoteOn(native_env::VoicecardBytes(v), 0) >= 0) voice = v;
  }
  CHECK(voice >= 0);
  native_env::ClearSpi();
  native_env::MidiIn3(0x80, 60, 0);
  native_env::Run(4);
  CHECK(CountByte(native_env::VoicecardBytes(voice), COMMAND_RELEASE) >= 1);
}

TEST(BootChordUsesEveryVoiceOfThePart) {
  native_env::Boot();
  uint8_t mask = multi.data().part_mapping_[0].voice_allocation;
  for (uint8_t n = 0; n < PopCount(mask); ++n) {
    native_env::MidiIn3(0x90, 48 + n * 3, 64);
  }
  native_env::Run(8);
  for (uint8_t v = 0; v < kNumVoices; ++v) {
    bool got_note = FindNoteOn(native_env::VoicecardBytes(v), 0) >= 0;
    CHECK_MSG(got_note == !!(mask & (1 << v)),
              "voice %d: note %d, in part mask %d", v, got_note,
              !!(mask & (1 << v)));
  }
}

TEST(BootRunningStatusAndZeroVelocityNoteOff) {
  native_env::Boot();
  // 0x90 60 100, then running status: 60 0 (= note off).
  const uint8_t m[] = { 0x90, 60, 100, 60, 0 };
  native_env::MidiIn(m, sizeof(m));
  native_env::Run(4);
  int releases = 0;
  for (uint8_t v = 0; v < kNumVoices; ++v) {
    releases += CountByte(native_env::VoicecardBytes(v), COMMAND_RELEASE);
  }
  CHECK(releases >= 1);
}
