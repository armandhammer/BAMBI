// SysEx protocol through the headless controller: dumps, requests, YAM+
// version/locations replies, checksums and malformed input.
#include "test.h"
#include "controller_env.h"

#include <stddef.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <vector>

#include "common/patch.h"
#include "common/protocol.h"
#include "controller/multi.h"
#include "controller/parameter.h"
#include "controller/part.h"
#include "controller/storage.h"

using namespace ambika;

namespace {

const uint8_t kHeader[] = { 0xf0, 0x00, 0x21, 0x02, 0x00, 0x04 };

std::vector<uint8_t> Message(uint8_t command, uint8_t argument,
                             const uint8_t* data, size_t size,
                             int checksum_delta = 0) {
  std::vector<uint8_t> m(kHeader, kHeader + sizeof(kHeader));
  m.push_back(command);
  m.push_back(argument);
  uint8_t checksum = 0;
  for (size_t i = 0; i < size; ++i) {
    m.push_back(data[i] >> 4);
    m.push_back(data[i] & 0x0f);
    checksum += data[i];
  }
  checksum += checksum_delta;
  m.push_back(checksum >> 4);
  m.push_back(checksum & 0x0f);
  m.push_back(0xf7);
  return m;
}

struct Reply {
  bool ok;
  uint8_t command;
  uint8_t argument;
  std::vector<uint8_t> data;
};

// Finds the first Ambika SysEx message with |command| in |bytes| and
// decodes it, checking the checksum. MIDI out also echoes what came in
// (thru), so requests show up there too.
Reply FindReply(const std::vector<uint8_t>& bytes, uint8_t command) {
  Reply r;
  r.ok = false;
  for (size_t i = 0; i + sizeof(kHeader) + 4 < bytes.size(); ++i) {
    if (memcmp(&bytes[i], kHeader, sizeof(kHeader)) != 0) continue;
    size_t p = i + sizeof(kHeader);
    if (bytes[p] != command) continue;
    r.command = bytes[p++];
    r.argument = bytes[p++];
    size_t end = p;
    while (end < bytes.size() && bytes[end] != 0xf7) ++end;
    if (end == bytes.size() || ((end - p) & 1)) return r;
    for (size_t j = p; j < end; j += 2) {
      r.data.push_back((bytes[j] << 4) | bytes[j + 1]);
    }
    if (r.data.empty()) return r;
    uint8_t checksum = r.data.back();
    r.data.pop_back();
    uint8_t sum = 0;
    for (size_t j = 0; j < r.data.size(); ++j) sum += r.data[j];
    r.ok = sum == checksum;
    return r;
  }
  return r;
}

void Send(const std::vector<uint8_t>& m) {
  native_env::MidiIn(m);
  native_env::Run(4);
}

std::vector<uint8_t> PatchOf(uint8_t part) {
  const uint8_t* p = multi.part(part).raw_patch_data();
  return std::vector<uint8_t>(p, p + sizeof(Patch));
}

// A valid patch that differs from the default one.
std::vector<uint8_t> TestPatch(uint8_t seed) {
  std::vector<uint8_t> p = PatchOf(0);
  p[offsetof(Patch, osc[0].shape)] = WAVEFORM_POLYBLEP_PWM;
  p[offsetof(Patch, osc[0].parameter)] = 10 + seed;
  p[offsetof(Patch, filter[0].cutoff)] = 40 + seed;
  p[offsetof(Patch, vintage)] = 30 + seed;
  return p;
}

}  // namespace

TEST(SysExVersionReply) {
  native_env::Boot();
  native_env::SetVoicecards(0x3f & ~(1 << 4), 1, 0x11);  // port 5 empty
  native_env::ClearMidiOut();
  Send(Message(0x1c, 0, 0, 0));
  Reply r = FindReply(native_env::MidiOut(), 0x0c);
  CHECK(r.ok);
  CHECK_EQ(r.data.size(), 18);
  CHECK_EQ(r.data[0], 1);  // family: YAM+
  CHECK_EQ(r.data[3], WAVEFORM_LAST);
  for (uint8_t port = 0; port < 6; ++port) {
    uint8_t id = r.data[6 + 2 * port];
    uint8_t version = r.data[7 + 2 * port];
    if (port == 4) {
      CHECK_MSG(id == 0xff, "absent port 5 reports id %d", id);
    } else {
      CHECK_MSG(id == 1 && version == 0x11, "port %d: id %d version %d",
                port + 1, id, version);
    }
  }
}

TEST(SysExPatchRequestRepliesWithPartTag) {
  native_env::Boot();
  native_env::ClearMidiOut();
  Send(Message(0x11, 2, 0, 0));  // patch of part 2
  Reply r = FindReply(native_env::MidiOut(), 0x01);
  CHECK(r.ok);
  CHECK_EQ(r.argument, 2);
  CHECK(r.data == PatchOf(1));
}

TEST(SysExPatchDumpRoundTrip) {
  native_env::Boot();
  std::vector<uint8_t> patch = TestPatch(3);
  Send(Message(0x01, 3, &patch[0], patch.size()));
  CHECK(PatchOf(2) == patch);
  CHECK(PatchOf(0) != patch);
  native_env::ClearMidiOut();
  Send(Message(0x11, 3, 0, 0));
  Reply r = FindReply(native_env::MidiOut(), 0x01);
  CHECK(r.ok);
  CHECK(r.data == patch);
}

TEST(SysExPatchDumpIsSentToThePartsVoicecards) {
  native_env::Boot();
  uint8_t mask = multi.data().part_mapping_[0].voice_allocation;
  std::vector<uint8_t> patch = TestPatch(5);
  native_env::ClearSpi();
  Send(Message(0x01, 1, &patch[0], patch.size()));
  for (uint8_t v = 0; v < kNumVoices; ++v) {
    const std::vector<uint8_t>& b = native_env::VoicecardBytes(v);
    // Block write: COMMAND_BULK_SEND, then size, then the raw patch.
    bool found = false;
    for (size_t i = 0; i + 1 + sizeof(Patch) <= b.size(); ++i) {
      if (b[i] == sizeof(Patch) &&
          memcmp(&b[i + 1], &patch[0], sizeof(Patch)) == 0) {
        found = true;
      }
    }
    CHECK_MSG(found == !!(mask & (1 << v)), "voice %d: block %d, in part %d",
              v, found, !!(mask & (1 << v)));
  }
}

TEST(SysExBadChecksumIsRejected) {
  native_env::Boot();
  std::vector<uint8_t> before = PatchOf(0);
  std::vector<uint8_t> patch = TestPatch(1);
  Send(Message(0x01, 1, &patch[0], patch.size(), 1));
  CHECK(PatchOf(0) == before);
  CHECK_EQ(storage.sysex_rx_state(), RECEPTION_ERROR);
}

TEST(SysExForeignAndTruncatedMessagesAreIgnored) {
  native_env::Boot();
  std::vector<uint8_t> before = PatchOf(0);
  const uint8_t foreign[] = { 0xf0, 0x43, 0x10, 0x4c, 0x00, 0x00, 0x7e, 0x00,
                              0xf7 };
  native_env::MidiIn(foreign, sizeof(foreign));
  // A Mutable header for another product (Shruthi = 0x00 0x01).
  const uint8_t shruthi[] = { 0xf0, 0x00, 0x21, 0x02, 0x00, 0x01, 0x01, 0x00,
                              0xf7 };
  native_env::MidiIn(shruthi, sizeof(shruthi));
  // An Ambika patch dump cut off half way.
  std::vector<uint8_t> patch = TestPatch(2);
  std::vector<uint8_t> m = Message(0x01, 1, &patch[0], patch.size());
  m.resize(m.size() / 2);
  native_env::MidiIn(m);
  native_env::Run(4);
  CHECK(PatchOf(0) == before);
  // A complete message afterwards still works.
  Send(Message(0x01, 1, &patch[0], patch.size()));
  CHECK(PatchOf(0) == patch);
}

TEST(SysExShortForeignMessageDoesNotReplayLastCommand) {
  // Regression: a header mismatch went to the "expect F7, then accept"
  // state, with the previous message's command and checksum still in
  // place. A 3-byte foreign message (F0 7D F7) right after a patch dump
  // whose checksum happened to be 0 re-applied that patch.
  native_env::Boot();
  std::vector<uint8_t> patch = TestPatch(0);
  uint8_t sum = 0;
  for (size_t i = 0; i < patch.size(); ++i) sum += patch[i];
  patch[offsetof(Patch, padding)] -= sum;  // make the checksum 0
  Send(Message(0x01, 1, &patch[0], patch.size()));
  CHECK(PatchOf(0) == patch);
  // Edit the cutoff by NRPN, then send the foreign message.
  native_env::Nrpn(0, offsetof(Patch, filter[0].cutoff), 99);
  native_env::Run(4);
  CHECK_EQ(PatchOf(0)[offsetof(Patch, filter[0].cutoff)], 99);
  const uint8_t foreign[] = { 0xf0, 0x7d, 0xf7 };
  native_env::MidiIn(foreign, sizeof(foreign));
  native_env::Run(4);
  CHECK_MSG(PatchOf(0)[offsetof(Patch, filter[0].cutoff)] == 99,
            "foreign SysEx replayed the previous patch dump");
}

TEST(SysExPartArgumentOutOfRangeIsRejected) {
  // Regression: the argument (part 1-6, 0 = active part) was not checked.
  // A patch dump with argument 7..127 wrote 112 bytes past the parts.
  native_env::Boot();
  std::vector<uint8_t> patch = TestPatch(4);
  std::vector<uint8_t> parts_before;
  for (uint8_t p = 0; p < kNumParts; ++p) {
    std::vector<uint8_t> x = PatchOf(p);
    parts_before.insert(parts_before.end(), x.begin(), x.end());
  }
  MultiData multi_before = multi.data();
  for (uint8_t argument = 7; argument < 128; argument += 15) {
    Send(Message(0x01, argument, &patch[0], patch.size()));
    CHECK_EQ(storage.sysex_rx_state(), RECEPTION_ERROR);
    native_env::ClearMidiOut();
    Send(Message(0x11, argument, 0, 0));
    CHECK_MSG(!FindReply(native_env::MidiOut(), 0x01).ok,
              "request for part %d answered", argument);
  }
  std::vector<uint8_t> parts_after;
  for (uint8_t p = 0; p < kNumParts; ++p) {
    std::vector<uint8_t> x = PatchOf(p);
    parts_after.insert(parts_after.end(), x.begin(), x.end());
  }
  CHECK(parts_after == parts_before);
  CHECK(memcmp(&multi_before, &multi.data(), sizeof(MultiData)) == 0);
}

TEST(SysExLocationsReply) {
  native_env::Boot();
  native_env::ClearMidiOut();
  Send(Message(0x1a, 0, 0, 0));
  Reply r = FindReply(native_env::MidiOut(), 0x0a);
  CHECK(r.ok);
  CHECK_EQ(r.data.size(), (kNumVoices * 3 + 1) * 2);
}

TEST(SysExMultiDumpRoundTrip) {
  native_env::Boot();
  native_env::ClearMidiOut();
  Send(Message(0x14, 0, 0, 0));
  Reply r = FindReply(native_env::MidiOut(), 0x04);
  CHECK(r.ok);
  CHECK_EQ(r.data.size(), sizeof(MultiData));
  std::vector<uint8_t> m = r.data;
  m[offsetof(MultiData, clock_bpm)] = 133;
  Send(Message(0x04, 0, &m[0], m.size()));
  CHECK_EQ(multi.data().clock_bpm, 133);
}

TEST(SysExPartDataIsClamped) {
  // Part settings (0x05) go through the same clamp: a steal or spread mode
  // past the end of its list would index past the value strings.
  native_env::Boot();
  const uint8_t* raw = multi.part(0).raw_data();
  std::vector<uint8_t> part(raw, raw + sizeof(PartData));
  part[offsetof(PartData, steal_mode)] = 0x55;
  part[offsetof(PartData, spread_mode)] = 9;
  part[offsetof(PartData, legato)] = 1;
  Send(Message(0x05, 1, &part[0], part.size()));
  CHECK(multi.part(0).data().steal_mode < STEAL_MODE_LAST);
  CHECK(multi.part(0).data().spread_mode < SPREAD_MODE_LAST);
  CHECK_EQ(multi.part(0).data().legato, 1);
}

TEST(SysExOutOfRangePatchValuesAreClamped) {
  // A patch dump with values outside the parameter ranges (another firmware,
  // a corrupt file, an editor bug) must not reach the voicecards as is: an
  // oscillator shape past WAVEFORM_LAST indexes past the voicecard's
  // function table.
  native_env::Boot();
  std::vector<uint8_t> patch = TestPatch(0);
  patch[offsetof(Patch, osc[0].shape)] = 200;
  patch[offsetof(Patch, osc[1].shape)] = WAVEFORM_LAST;
  patch[offsetof(Patch, mix_op)] = 99;
  patch[offsetof(Patch, modulation[3].source)] = 250;
  patch[offsetof(Patch, modulation[3].amount)] = 0x80;  // -128
  patch[offsetof(Patch, env_lfo[1].attack)] = 255;
  patch[offsetof(Patch, env_curve[2])] = 200;
  native_env::ClearSpi();
  Send(Message(0x01, 1, &patch[0], patch.size()));
  std::vector<uint8_t> p = PatchOf(0);
  CHECK(p[offsetof(Patch, osc[0].shape)] < WAVEFORM_LAST);
  CHECK(p[offsetof(Patch, osc[1].shape)] < WAVEFORM_LAST);
  CHECK(p[offsetof(Patch, mix_op)] < OP_LAST);
  CHECK(p[offsetof(Patch, modulation[3].source)] < MOD_SRC_LAST);
  CHECK_EQ(static_cast<int8_t>(p[offsetof(Patch, modulation[3].amount)]), -63);
  CHECK(p[offsetof(Patch, env_lfo[1].attack)] <= 127);
  CHECK(p[offsetof(Patch, env_curve[2])] <= 127);
  // In-range values are untouched.
  CHECK_EQ(p[offsetof(Patch, filter[0].cutoff)],
           patch[offsetof(Patch, filter[0].cutoff)]);
  CHECK_EQ(p[offsetof(Patch, vintage)], patch[offsetof(Patch, vintage)]);
  // And the voicecards got the clamped patch.
  uint8_t mask = multi.data().part_mapping_[0].voice_allocation;
  for (uint8_t v = 0; v < kNumVoices; ++v) {
    if (!(mask & (1 << v))) continue;
    const std::vector<uint8_t>& b = native_env::VoicecardBytes(v);
    bool found = false;
    for (size_t i = 0; i + 1 + sizeof(Patch) <= b.size(); ++i) {
      found |= b[i] == sizeof(Patch) &&
          memcmp(&b[i + 1], &p[0], sizeof(Patch)) == 0;
    }
    CHECK_MSG(found, "voice %d did not get the clamped patch", v);
  }
}

TEST(SysExValidPatchesAreNotModified) {
  // Sanitizing must be a no-op for anything the parameter ranges allow.
  native_env::Boot();
  uint32_t seed = 7;
  for (int round = 0; round < 50; ++round) {
    std::vector<uint8_t> patch = PatchOf(0);
    for (uint8_t i = 0; i < kNumParameters; ++i) {
      Parameter q = parameter_manager.parameter(i);
      if (q.level != PARAMETER_LEVEL_PATCH) continue;
      for (uint8_t k = 0; k < q.num_instances; ++k) {
        seed = seed * 1103515245u + 12345u;
        int lo = q.unit == UNIT_INT8 ? static_cast<int8_t>(q.min_value)
                                     : q.min_value;
        int hi = q.unit == UNIT_INT8 ? static_cast<int8_t>(q.max_value)
                                     : q.max_value;
        int v = lo + static_cast<int>((seed >> 16) % (hi - lo + 1));
        patch[q.offset + q.stride * k] = static_cast<uint8_t>(v);
      }
    }
    Send(Message(0x01, 1, &patch[0], patch.size()));
    CHECK_MSG(PatchOf(0) == patch, "round %d: a valid patch was modified",
              round);
  }
}
