// VoiceAllocator (controller/voice_allocator.cc): LRU poly allocation,
// note retrigger, stealing, and the cyclic mode.
#include "test.h"

#include "controller/voice_allocator.h"

using ambika::VoiceAllocator;

namespace {

struct Allocator {
  uint8_t pool[6];
  uint8_t lru[6];
  VoiceAllocator a;
  Allocator(uint8_t size, bool cyclic) { a.Init(size, cyclic, pool, lru); }
};

}  // namespace

TEST(VoiceAllocatorPolyUsesEveryVoiceBeforeStealing) {
  Allocator x(6, false);
  bool used[6] = { false };
  for (uint8_t n = 0; n < 6; ++n) {
    uint8_t v = x.a.NoteOn(60 + n);
    CHECK(v < 6);
    CHECK_MSG(!used[v], "voice %d allocated twice for 6 held notes", v);
    used[v] = true;
  }
}

TEST(VoiceAllocatorPolyStealsLeastRecentlyPlayed) {
  Allocator x(4, false);
  uint8_t v60 = x.a.NoteOn(60);
  x.a.NoteOn(62);
  x.a.NoteOn(64);
  x.a.NoteOn(65);
  // All four held: the fifth note takes the oldest one (60).
  CHECK_EQ(x.a.NoteOn(67), v60);
  CHECK_EQ(x.a.FindActive(60), 0xff);
  CHECK_EQ(x.a.FindActive(67), v60);
}

TEST(VoiceAllocatorPolyPrefersReleasedVoices) {
  Allocator x(4, false);
  x.a.NoteOn(60);
  uint8_t v62 = x.a.NoteOn(62);
  x.a.NoteOn(64);
  x.a.NoteOn(65);
  x.a.NoteOff(62);
  // 60 is the oldest note but it is still held; 62 was released.
  CHECK_EQ(x.a.NoteOn(70), v62);
  CHECK(x.a.FindActive(60) != 0xff);
}

TEST(VoiceAllocatorPolyRetriggersSameNoteOnSameVoice) {
  Allocator x(6, false);
  uint8_t v = x.a.NoteOn(60);
  x.a.NoteOn(64);
  CHECK_EQ(x.a.NoteOn(60), v);
  x.a.NoteOff(60);
  // Released, then played again: still the same voice (keeps its tail).
  CHECK_EQ(x.a.NoteOn(60), v);
}

TEST(VoiceAllocatorPolyReleasedVoiceIsReusedLast) {
  // Round-robin feel: after releasing a voice, other free voices are used
  // before it, so release tails ring out.
  Allocator x(3, false);
  uint8_t a = x.a.NoteOn(60);
  x.a.NoteOff(60);
  uint8_t b = x.a.NoteOn(61);
  x.a.NoteOff(61);
  uint8_t c = x.a.NoteOn(62);
  x.a.NoteOff(62);
  CHECK(a != b && b != c && a != c);
  CHECK_EQ(x.a.NoteOn(63), a);
}

TEST(VoiceAllocatorNoteOffUnknownNoteIsHarmless) {
  Allocator x(4, false);
  x.a.NoteOn(60);
  CHECK_EQ(x.a.NoteOff(99), 0xff);
  CHECK(x.a.FindActive(60) != 0xff);
}

TEST(VoiceAllocatorSizeZeroRefusesNotes) {
  Allocator x(0, false);
  CHECK_EQ(x.a.NoteOn(60), 0xff);
}

TEST(VoiceAllocatorCyclicRotates) {
  Allocator x(4, true);
  CHECK_EQ(x.a.NoteOn(60), 1);
  CHECK_EQ(x.a.NoteOn(61), 2);
  CHECK_EQ(x.a.NoteOn(62), 3);
  CHECK_EQ(x.a.NoteOn(63), 0);
  CHECK_EQ(x.a.NoteOn(64), 1);
}

TEST(VoiceAllocatorCyclicNoteOffFindsVoice) {
  Allocator x(4, true);
  uint8_t v = x.a.NoteOn(60);
  CHECK_EQ(x.a.NoteOff(60), v);
  CHECK_EQ(x.a.FindActive(60), 0xff);
}

TEST(VoiceAllocatorEveryNoteValueWorks) {
  // Notes 0 and 127 are edge cases: the pool marks free slots as 0 (and,
  // in cyclic mode, released slots as 0xff = active bit + note 127).
  Allocator x(2, false);
  uint8_t v0 = x.a.NoteOn(0);
  uint8_t v127 = x.a.NoteOn(127);
  CHECK(v0 != v127);
  CHECK_EQ(x.a.FindActive(0), v0);
  CHECK_EQ(x.a.FindActive(127), v127);
  CHECK_EQ(x.a.NoteOff(0), v0);
  CHECK_EQ(x.a.NoteOff(127), v127);
  CHECK_EQ(x.a.FindActive(0), 0xff);
  CHECK_EQ(x.a.FindActive(127), 0xff);
}

TEST(VoiceAllocatorCyclicReleasedSlotIsNotANote127) {
  // Cyclic NoteOff writes 0xff into the slot. That must not make the slot
  // look like a held note 127.
  Allocator x(2, true);
  x.a.NoteOn(60);
  x.a.NoteOff(60);
  CHECK_EQ(x.a.FindActive(127), 0xff);
}

TEST(VoiceAllocatorStressNeverReturnsOutOfRange) {
  Allocator x(6, false);
  uint32_t seed = 12345;
  for (int i = 0; i < 20000; ++i) {
    seed = seed * 1103515245u + 12345u;
    uint8_t note = (seed >> 16) & 0x7f;
    if ((seed >> 24) & 1) {
      uint8_t v = x.a.NoteOn(note);
      CHECK_MSG(v < 6, "NoteOn(%d) returned %d", note, v);
      CHECK_EQ(x.a.FindActive(note), v);
    } else {
      uint8_t v = x.a.NoteOff(note);
      CHECK(v == 0xff || v < 6);
    }
    // LRU must stay a permutation of 0..5.
    uint8_t seen = 0;
    for (int j = 0; j < 6; ++j) {
      CHECK(x.lru[j] < 6);
      seen |= 1 << x.lru[j];
    }
    CHECK_EQ(seen, 0x3f);
  }
}
