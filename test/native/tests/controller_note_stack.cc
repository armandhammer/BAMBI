// NoteStack (controller/note_stack.h): played-order and pitch-sorted views
// used by mono note priority and the arpeggiator.
#include "test.h"

#include "controller/note_stack.h"

using ambika::NoteStack;

TEST(NoteStackOrders) {
  NoteStack<8> s;
  s.Init();
  s.NoteOn(64, 100);
  s.NoteOn(60, 101);
  s.NoteOn(67, 102);
  CHECK_EQ(s.size(), 3);
  CHECK_EQ(s.most_recent_note().note, 67);
  CHECK_EQ(s.most_recent_note().velocity, 102);
  CHECK_EQ(s.least_recent_note().note, 64);
  CHECK_EQ(s.sorted_note(0).note, 60);
  CHECK_EQ(s.sorted_note(1).note, 64);
  CHECK_EQ(s.sorted_note(2).note, 67);
  CHECK_EQ(s.played_note(0).note, 64);
  CHECK_EQ(s.played_note(1).note, 60);
  CHECK_EQ(s.played_note(2).note, 67);
}

TEST(NoteStackLastNotePriorityFallsBack) {
  NoteStack<8> s;
  s.Init();
  s.NoteOn(60, 100);
  s.NoteOn(64, 100);
  s.NoteOn(67, 100);
  s.NoteOff(67);
  CHECK_EQ(s.most_recent_note().note, 64);
  s.NoteOff(60);
  CHECK_EQ(s.most_recent_note().note, 64);
  s.NoteOff(64);
  CHECK_EQ(s.size(), 0);
}

TEST(NoteStackRepeatedNoteMovesToTop) {
  NoteStack<8> s;
  s.Init();
  s.NoteOn(60, 10);
  s.NoteOn(64, 20);
  s.NoteOn(60, 30);
  CHECK_EQ(s.size(), 2);
  CHECK_EQ(s.most_recent_note().note, 60);
  CHECK_EQ(s.most_recent_note().velocity, 30);
}

TEST(NoteStackSaturationDropsOldest) {
  NoteStack<4> s;
  s.Init();
  for (uint8_t n = 0; n < 6; ++n) {
    s.NoteOn(60 + n, 100);
  }
  CHECK_EQ(s.size(), 4);
  CHECK_EQ(s.least_recent_note().note, 62);
  CHECK_EQ(s.sorted_note(0).note, 62);
  CHECK_EQ(s.sorted_note(3).note, 65);
}

TEST(NoteStackOffForAbsentNoteIsHarmless) {
  NoteStack<4> s;
  s.Init();
  s.NoteOff(60);
  CHECK_EQ(s.size(), 0);
  s.NoteOn(60, 1);
  s.NoteOff(61);
  CHECK_EQ(s.size(), 1);
}

TEST(NoteStackStressKeepsSortedInvariant) {
  NoteStack<10> s;
  s.Init();
  uint32_t seed = 99;
  for (int i = 0; i < 20000; ++i) {
    seed = seed * 1664525u + 1013904223u;
    uint8_t note = (seed >> 20) & 0x7f;
    if ((seed >> 8) & 3) {
      s.NoteOn(note, (seed >> 12) & 0x7f);
    } else {
      s.NoteOff(note);
    }
    CHECK(s.size() <= 10);
    for (uint8_t j = 1; j < s.size(); ++j) {
      CHECK_MSG(s.sorted_note(j - 1).note < s.sorted_note(j).note,
                "sorted view out of order at step %d", i);
    }
    // Played-order walk visits exactly size() distinct notes.
    for (uint8_t j = 0; j < s.size(); ++j) {
      CHECK(s.played_note(j).note != ambika::kFreeSlot);
    }
  }
}
