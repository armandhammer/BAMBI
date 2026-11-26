// Polyphony modes through the headless controller (Part + VoiceAllocator).
#include "test.h"
#include "controller_env.h"

#include "common/protocol.h"
#include "controller/multi.h"
#include "controller/part.h"

using namespace ambika;

namespace {

// Gives part 1 all six voicecards and the given polyphony mode.
void SetUpPart(uint8_t polyphony_mode) {
  native_env::Boot();
  for (uint8_t i = 0; i < kNumParts; ++i) {
    multi.mutable_data()->part_mapping_[i].voice_allocation = i == 0 ? 0x3f : 0;
  }
  multi.AssignVoicesToParts();
  native_env::Nrpn(0, PRM_PART_POLYPHONY_MODE, polyphony_mode);
  native_env::Run(4);
  native_env::ClearSpi();
}

// Number of "write modulation source = aftertouch" commands per slave.
int AftertouchWrites(uint8_t slave) {
  const std::vector<uint8_t>& b = native_env::VoicecardBytes(slave);
  int n = 0;
  for (size_t i = 0; i + 1 < b.size(); ++i) {
    if (b[i] == COMMAND_WRITE_MOD_MATRIX && b[i + 1] == MOD_SRC_AFTERTOUCH) {
      ++n;
    }
  }
  return n;
}

bool HasNoteOn(uint8_t slave) {
  const std::vector<uint8_t>& b = native_env::VoicecardBytes(slave);
  for (size_t i = 0; i < b.size(); ++i) {
    if (b[i] == COMMAND_NOTE_ON) return true;
  }
  return false;
}

}  // namespace

TEST(PolyModeNrpnSelectsMode) {
  SetUpPart(CHAIN);
  CHECK_EQ(multi.part(0).data().polyphony_mode, CHAIN);
}

TEST(ChainModePlaysLocalNotesThenForwards) {
  SetUpPart(CHAIN);
  native_env::ClearMidiOut();
  for (uint8_t n = 0; n < 8; ++n) {
    native_env::MidiIn3(0x90, 60 + n, 100);
  }
  native_env::Run(8);
  for (uint8_t v = 0; v < kNumVoices; ++v) {
    CHECK_MSG(HasNoteOn(v), "voice %d silent", v);
  }
}

TEST(ChainModePolyAftertouchStaysOnRealVoices) {
  // Regression: Part::Aftertouch halved the allocator size for CYCLIC
  // instead of CHAIN. In CHAIN mode the allocator is twice the number of
  // local voices; aftertouch on a forwarded note indexed past
  // allocated_voices_[] and wrote to a garbage SPI slave.
  SetUpPart(CHAIN);
  for (uint8_t n = 0; n < 12; ++n) {
    native_env::MidiIn3(0x90, 60 + n, 100);
  }
  native_env::Run(8);
  native_env::ClearSpi();
  // Notes 66..71 were forwarded down the chain.
  for (uint8_t n = 66; n < 72; ++n) {
    native_env::MidiIn3(0xa0, n, 90);
  }
  native_env::Run(8);
  for (uint8_t slave = 0; slave < 8; ++slave) {
    CHECK_MSG(AftertouchWrites(slave) == 0,
              "aftertouch for a forwarded note reached SPI slave %d", slave);
  }
  // Local notes still get theirs.
  native_env::MidiIn3(0xa0, 60, 90);
  native_env::Run(8);
  int total = 0;
  for (uint8_t slave = 0; slave < kNumVoices; ++slave) {
    total += AftertouchWrites(slave);
  }
  CHECK_EQ(total, 1);
}

TEST(CyclicModePolyAftertouchReachesEveryVoice) {
  // Same regression: in CYCLIC mode, notes on the upper half of the voices
  // never received poly aftertouch.
  SetUpPart(CYCLIC);
  for (uint8_t n = 0; n < 6; ++n) {
    native_env::MidiIn3(0x90, 60 + n, 100);
  }
  native_env::Run(8);
  native_env::ClearSpi();
  for (uint8_t n = 0; n < 6; ++n) {
    native_env::MidiIn3(0xa0, 60 + n, 90);
  }
  native_env::Run(8);
  for (uint8_t v = 0; v < kNumVoices; ++v) {
    CHECK_MSG(AftertouchWrites(v) == 1, "voice %d: %d aftertouch writes", v,
              AftertouchWrites(v));
  }
}

TEST(CyclicModeNote127IsReleased) {
  // Regression: cyclic NoteOff marked released slots 0xff, which reads as
  // "active, note 127". Releasing a real note 127 could hit a stale slot
  // and leave the voice playing 127 stuck.
  SetUpPart(CYCLIC);
  native_env::MidiIn3(0x90, 60, 100);  // slot A
  native_env::MidiIn3(0x80, 60, 0);    // slot A released
  native_env::MidiIn3(0x90, 127, 100);
  native_env::Run(8);
  int voice = -1;
  for (uint8_t v = 0; v < kNumVoices; ++v) {
    const std::vector<uint8_t>& b = native_env::VoicecardBytes(v);
    for (size_t i = 0; i + 2 < b.size(); ++i) {
      if (b[i] == COMMAND_NOTE_ON && ((b[i + 1] << 8 | b[i + 2]) + 64) >> 7 == 127) {
        voice = v;
      }
    }
  }
  CHECK(voice >= 0);
  native_env::ClearSpi();
  native_env::MidiIn3(0x80, 127, 0);
  native_env::Run(8);
  const std::vector<uint8_t>& b = native_env::VoicecardBytes(voice);
  bool released = false;
  for (size_t i = 0; i < b.size(); ++i) released |= b[i] == COMMAND_RELEASE;
  CHECK_MSG(released, "voice %d playing note 127 was not released", voice);
}

TEST(UnisonModeStacksTwoVoicesPerNote) {
  SetUpPart(UNISON_2X);
  native_env::MidiIn3(0x90, 60, 100);
  native_env::Run(8);
  int voices = 0;
  for (uint8_t v = 0; v < kNumVoices; ++v) voices += HasNoteOn(v);
  CHECK_EQ(voices, 2);
}

TEST(MonoModeTriggersAllVoicesLegato) {
  SetUpPart(MONO);
  native_env::MidiIn3(0x90, 60, 100);
  native_env::Run(8);
  int voices = 0;
  for (uint8_t v = 0; v < kNumVoices; ++v) voices += HasNoteOn(v);
  CHECK_EQ(voices, kNumVoices);
}
