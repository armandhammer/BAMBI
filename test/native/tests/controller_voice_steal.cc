// Voice steal modes (BAMBI, part byte 81 / NRPN 193): which held note a
// polyphonic part cuts when a new note finds every voice held.
#include "test.h"

#include <stddef.h>
#include <string.h>
#include "controller_env.h"

#include "common/protocol.h"
#include "controller/multi.h"
#include "controller/part.h"
#include "controller/system_settings.h"
#include "controller/voice_allocator.h"

using namespace ambika;

namespace {

struct Allocator {
  uint8_t pool[12];
  uint8_t lru[12];
  VoiceAllocator a;
  Allocator(uint8_t size, bool cyclic) { a.Init(size, cyclic, pool, lru); }
  // Plays the notes in order with |mode|; returns false if one was refused.
  bool Hold(const uint8_t* notes, uint8_t n, uint8_t mode) {
    bool ok = true;
    for (uint8_t i = 0; i < n; ++i) ok &= a.NoteOn(notes[i], mode) != 0xff;
    return ok;
  }
};

// Played out of pitch order so that "oldest" and "lowest" differ.
const uint8_t kChord[4] = { 64, 60, 72, 67 };

// Pitch (1/128 semitone) of the last note-on sent to |slave|, or -1.
int LastNoteOnPitch(uint8_t slave) {
  const std::vector<uint8_t>& b = native_env::VoicecardBytes(slave);
  int pitch = -1;
  for (size_t i = 0; i + 3 < b.size(); ++i) {
    if (b[i] == COMMAND_NOTE_ON) {
      pitch = b[i + 1] << 8 | b[i + 2];
      i += 3;
    }
  }
  return pitch;
}

int VoicesWithNoteOn() {
  int n = 0;
  for (uint8_t v = 0; v < kNumVoices; ++v) n += LastNoteOnPitch(v) >= 0;
  return n;
}

// Voicecards that got a note in a PlayAndCollect() result.
int Played(const int* voice_notes) {
  int n = 0;
  for (uint8_t v = 0; v < kNumVoices; ++v) n += voice_notes[v] >= 0;
  return n;
}

// Gives part 1 all six voicecards, a polyphony mode and a steal mode.
void SetUpPart(uint8_t polyphony_mode, uint8_t steal_mode) {
  native_env::Boot();
  for (uint8_t i = 0; i < kNumParts; ++i) {
    multi.mutable_data()->part_mapping_[i].voice_allocation = i == 0 ? 0x3f : 0;
  }
  multi.AssignVoicesToParts();
  native_env::Nrpn(0, PRM_PART_POLYPHONY_MODE, polyphony_mode);
  native_env::Nrpn(0, PRM_PART_STEAL_MODE, steal_mode);
  native_env::Run(4);
  native_env::ClearSpi();
  native_env::ClearMidiOut();
}

// Plays notes and returns the pitch each voicecard got (note number, -1 if
// none) after the last one.
void PlayAndCollect(const uint8_t* notes, uint8_t n, int* voice_notes) {
  for (uint8_t i = 0; i < n; ++i) native_env::MidiIn3(0x90, notes[i], 100);
  native_env::Run(8);
  for (uint8_t v = 0; v < kNumVoices; ++v) {
    int p = LastNoteOnPitch(v);
    voice_notes[v] = p < 0 ? -1 : (p + 64) >> 7;
  }
  native_env::ClearSpi();
}

bool MidiOutHasNoteOn(uint8_t note) {
  const std::vector<uint8_t>& b = native_env::MidiOut();
  for (size_t i = 0; i + 2 < b.size(); ++i) {
    if ((b[i] & 0xf0) == 0x90 && b[i + 1] == note && b[i + 2]) return true;
  }
  return false;
}

}  // namespace

// --- VoiceAllocator ---------------------------------------------------------

TEST(StealOldestIsTheDefaultAndMatchesYam) {
  Allocator x(4, false);
  CHECK(x.Hold(kChord, 4, STEAL_OLDEST));
  uint8_t v64 = x.a.FindActive(64);
  CHECK_EQ(x.a.NoteOn(50, STEAL_OLDEST), v64);
  CHECK_EQ(x.a.FindActive(64), 0xff);
  // The default argument is the YAM behaviour too.
  CHECK_EQ(x.a.NoteOn(90), x.a.FindActive(90));
  CHECK_EQ(x.a.FindActive(60), 0xff);
}

TEST(StealLowestCutsTheLowestHeldNote) {
  Allocator x(4, false);
  CHECK(x.Hold(kChord, 4, STEAL_LOWEST));
  uint8_t v60 = x.a.FindActive(60);
  CHECK_EQ(x.a.NoteOn(74, STEAL_LOWEST), v60);
  CHECK_EQ(x.a.FindActive(60), 0xff);
  CHECK(x.a.FindActive(64) != 0xff);
  // Next victim is 64, the lowest now.
  uint8_t v64 = x.a.FindActive(64);
  CHECK_EQ(x.a.NoteOn(65, STEAL_LOWEST), v64);
}

TEST(StealLowestRefusesANoteBelowEveryHeldNote) {
  Allocator x(4, false);
  CHECK(x.Hold(kChord, 4, STEAL_LOWEST));
  uint8_t pool[4];
  memcpy(pool, x.pool, 4);
  CHECK_EQ(x.a.NoteOn(59, STEAL_LOWEST), 0xff);
  CHECK(memcmp(pool, x.pool, 4) == 0);
  CHECK_EQ(x.a.FindActive(59), 0xff);
  // Its note off finds nothing.
  CHECK_EQ(x.a.NoteOff(59), 0xff);
  for (uint8_t i = 0; i < 4; ++i) CHECK(x.a.FindActive(kChord[i]) != 0xff);
}

TEST(StealHighestCutsTheHighestHeldNote) {
  Allocator x(4, false);
  CHECK(x.Hold(kChord, 4, STEAL_HIGHEST));
  uint8_t v72 = x.a.FindActive(72);
  CHECK_EQ(x.a.NoteOn(36, STEAL_HIGHEST), v72);
  CHECK_EQ(x.a.FindActive(72), 0xff);
  // 73 is above everything held now (64, 60, 67, 36): refused.
  CHECK_EQ(x.a.NoteOn(73, STEAL_HIGHEST), 0xff);
  // 66 is below 67: steals 67.
  uint8_t v67 = x.a.FindActive(67);
  CHECK_EQ(x.a.NoteOn(66, STEAL_HIGHEST), v67);
}

TEST(StealExtremesAtNotes0And127) {
  Allocator x(2, false);
  CHECK_EQ(x.a.NoteOn(0, STEAL_HIGHEST) != 0xff, true);
  CHECK_EQ(x.a.NoteOn(127, STEAL_HIGHEST) != 0xff, true);
  CHECK_EQ(x.a.NoteOn(126, STEAL_HIGHEST), x.a.FindActive(126));
  CHECK_EQ(x.a.FindActive(127), 0xff);
  Allocator y(2, false);
  y.a.NoteOn(0, STEAL_LOWEST);
  y.a.NoteOn(127, STEAL_LOWEST);
  CHECK_EQ(y.a.NoteOn(1, STEAL_LOWEST), y.a.FindActive(1));
  CHECK_EQ(y.a.FindActive(0), 0xff);
  CHECK_EQ(y.a.NoteOn(0, STEAL_LOWEST), 0xff);
}

TEST(StealNoneRefusesUntilAVoiceIsReleased) {
  Allocator x(4, false);
  CHECK(x.Hold(kChord, 4, STEAL_NONE));
  CHECK_EQ(x.a.NoteOn(80, STEAL_NONE), 0xff);
  CHECK_EQ(x.a.NoteOn(20, STEAL_NONE), 0xff);
  uint8_t v67 = x.a.NoteOff(67);
  CHECK_EQ(x.a.NoteOn(80, STEAL_NONE), v67);
  // Out-of-range modes (corrupt data) behave as "none", never steal oddly.
  CHECK_EQ(x.a.NoteOn(81, 0x7f), 0xff);
}

TEST(StealModesStillReuseReleasedVoicesFirst) {
  for (uint8_t mode = 0; mode < STEAL_MODE_LAST; ++mode) {
    Allocator x(4, false);
    CHECK(x.Hold(kChord, 4, mode));
    // kChord[3] (67) is released; 64, 60 and 72 stay held.
    uint8_t v67 = x.a.NoteOff(67);
    CHECK_MSG(x.a.NoteOn(10, mode) == v67, "mode %d", mode);
    for (uint8_t i = 0; i < 3; ++i) CHECK(x.a.FindActive(kChord[i]) != 0xff);
  }
}

TEST(StealModesRetriggerAHeldNoteOnItsVoice) {
  for (uint8_t mode = 0; mode < STEAL_MODE_LAST; ++mode) {
    Allocator x(4, false);
    CHECK(x.Hold(kChord, 4, mode));
    uint8_t v60 = x.a.FindActive(60);
    CHECK_MSG(x.a.NoteOn(60, mode) == v60, "mode %d", mode);
  }
}

TEST(StealModeIsIgnoredByCyclicMode) {
  Allocator x(4, true);
  CHECK(x.Hold(kChord, 4, STEAL_NONE));
  CHECK_EQ(x.a.NoteOn(80, STEAL_NONE), 1);
  CHECK_EQ(x.a.NoteOn(10, STEAL_LOWEST), 2);
}

TEST(StealModesStressKeepTheLruAPermutation) {
  for (uint8_t mode = 0; mode < STEAL_MODE_LAST; ++mode) {
    Allocator x(6, false);
    uint32_t seed = 777 + mode;
    for (int i = 0; i < 20000; ++i) {
      seed = seed * 1103515245u + 12345u;
      uint8_t note = (seed >> 16) & 0x7f;
      if ((seed >> 24) & 1) {
        uint8_t was_active = x.a.FindActive(note);
        uint8_t v = x.a.NoteOn(note, mode);
        if (v == 0xff) {
          // Only refused when every voice is held, and never a held note.
          CHECK(was_active == 0xff);
          for (int j = 0; j < 6; ++j) CHECK(x.pool[j] & 0x80);
          CHECK(mode != STEAL_OLDEST);
        } else {
          CHECK(v < 6);
          CHECK_EQ(x.a.FindActive(note), v);
        }
      } else {
        x.a.NoteOff(note);
      }
      uint8_t seen = 0;
      for (int j = 0; j < 6; ++j) {
        CHECK(x.lru[j] < 6);
        seen |= 1 << x.lru[j];
      }
      CHECK_EQ(seen, 0x3f);
    }
  }
}

// --- Part (headless controller) ---------------------------------------------

TEST(StealModeNrpnSetsAndClamps) {
  SetUpPart(POLY, STEAL_HIGHEST);
  CHECK_EQ(multi.part(0).data().steal_mode, STEAL_HIGHEST);
  CHECK_EQ(PRM_PART_STEAL_MODE, sizeof(Patch) + offsetof(PartData,
                                                         steal_mode));
  native_env::Nrpn(0, PRM_PART_STEAL_MODE, 9);
  native_env::Run(2);
  CHECK(multi.part(0).data().steal_mode < STEAL_MODE_LAST);
  // Loading a part clamps it too: SysExPartDataIsClamped (controller_sysex.cc).
}

TEST(StealModeDefaultsToOldestOnANewPart) {
  native_env::Boot();
  for (uint8_t i = 0; i < kNumParts; ++i) {
    CHECK_EQ(multi.part(i).data().steal_mode, STEAL_OLDEST);
  }
}

TEST(PolyStealLowestKeepsTheMelody) {
  SetUpPart(POLY, STEAL_LOWEST);
  const uint8_t chord[6] = { 48, 55, 60, 64, 67, 72 };
  int voices[kNumVoices];
  PlayAndCollect(chord, 6, voices);
  int v48 = -1;
  for (uint8_t v = 0; v < kNumVoices; ++v) if (voices[v] == 48) v48 = v;
  CHECK(v48 >= 0);
  // Below every held note: not played.
  const uint8_t low[1] = { 43 };
  PlayAndCollect(low, 1, voices);
  CHECK_EQ(Played(voices), 0);
  for (uint8_t v = 0; v < kNumVoices; ++v) CHECK_EQ(voices[v], -1);
  // A melody note takes the bass note's voice.
  const uint8_t high[1] = { 76 };
  PlayAndCollect(high, 1, voices);
  CHECK_EQ(voices[v48], 76);
  for (uint8_t v = 0; v < kNumVoices; ++v) if (v != v48) CHECK_EQ(voices[v], -1);
}

TEST(PolyStealHighestKeepsTheBass) {
  SetUpPart(POLY, STEAL_HIGHEST);
  const uint8_t chord[6] = { 36, 48, 55, 60, 64, 67 };
  int voices[kNumVoices];
  PlayAndCollect(chord, 6, voices);
  int v67 = -1;
  for (uint8_t v = 0; v < kNumVoices; ++v) if (voices[v] == 67) v67 = v;
  CHECK(v67 >= 0);
  const uint8_t top[1] = { 70 };
  PlayAndCollect(top, 1, voices);
  CHECK_EQ(Played(voices), 0);
  const uint8_t mid[1] = { 62 };
  PlayAndCollect(mid, 1, voices);
  CHECK_EQ(voices[v67], 62);
}

TEST(Unison3xStealLowestCutsTheLowerStack) {
  SetUpPart(UNISON_3X, STEAL_LOWEST);
  const uint8_t two[2] = { 64, 60 };
  int voices[kNumVoices];
  PlayAndCollect(two, 2, voices);
  bool on60[kNumVoices];
  for (uint8_t v = 0; v < kNumVoices; ++v) on60[v] = voices[v] == 60;
  const uint8_t low[1] = { 55 };
  PlayAndCollect(low, 1, voices);
  CHECK_EQ(Played(voices), 0);
  const uint8_t high[1] = { 67 };
  PlayAndCollect(high, 1, voices);
  CHECK_EQ(Played(voices), 3);
  for (uint8_t v = 0; v < kNumVoices; ++v) {
    CHECK_MSG((voices[v] == 67) == on60[v], "voice %d got %d", v, voices[v]);
  }
}

TEST(ChainStealNoneDoesNotForwardRefusedNotes) {
  SetUpPart(CHAIN, STEAL_NONE);
  system_settings.mutable_data()->midi_out_mode = MIDI_OUT_CHAIN;
  // 6 local voices + 6 forwarded slots.
  for (uint8_t n = 0; n < 12; ++n) native_env::MidiIn3(0x90, 40 + n, 100);
  native_env::Run(8);
  CHECK(MidiOutHasNoteOn(51));  // forwarded: the chain works in this setup
  native_env::ClearMidiOut();
  native_env::ClearSpi();
  native_env::MidiIn3(0x90, 80, 100);
  native_env::Run(8);
  CHECK(!MidiOutHasNoteOn(80));
  CHECK_EQ(VoicesWithNoteOn(), 0);
  // A local note released frees its slot for the next note.
  native_env::MidiIn3(0x80, 40, 0);
  native_env::MidiIn3(0x90, 80, 100);
  native_env::Run(8);
  CHECK_EQ(VoicesWithNoteOn(), 1);
}

TEST(CyclicIgnoresStealNone) {
  SetUpPart(CYCLIC, STEAL_NONE);
  const uint8_t notes[7] = { 60, 61, 62, 63, 64, 65, 66 };
  int voices[kNumVoices];
  PlayAndCollect(notes, 7, voices);
  int found = 0;
  for (uint8_t v = 0; v < kNumVoices; ++v) found += voices[v] == 66;
  CHECK_EQ(found, 1);
}

TEST(StealModeCc115) {
  SetUpPart(POLY, STEAL_OLDEST);
  // CC 115 scales 0..127 onto the 4 modes.
  native_env::MidiIn3(0xb0, 115, 127);
  native_env::Run(2);
  CHECK_EQ(multi.part(0).data().steal_mode, STEAL_NONE);
  native_env::MidiIn3(0xb0, 115, 40);
  native_env::Run(2);
  CHECK_EQ(multi.part(0).data().steal_mode, STEAL_LOWEST);
}
