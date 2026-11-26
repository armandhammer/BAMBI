// Parameter table (controller/parameter.cc): ranges, offsets, the NRPN and
// CC maps, and the Clamp/Scale/Increment helpers, checked exhaustively.
#include "test.h"
#include "controller_env.h"

#include <stddef.h>
#include <vector>
#include <avr/pgmspace.h>

#include "common/patch.h"
#include "controller/multi.h"
#include "controller/parameter.h"
#include "controller/part.h"
#include "controller/system_settings.h"

using namespace ambika;

namespace {

int Signed(const Parameter& p, uint8_t v) {
  return p.unit == UNIT_INT8 ? static_cast<int8_t>(v) : v;
}

bool InRange(const Parameter& p, uint8_t v) {
  return Signed(p, v) >= Signed(p, p.min_value) &&
         Signed(p, v) <= Signed(p, p.max_value);
}

// Bytes addressable at this parameter's level (offset + stride * instance).
size_t LevelSize(const Parameter& p) {
  switch (p.level) {
    case PARAMETER_LEVEL_PATCH:
    case PARAMETER_LEVEL_PART:
      return sizeof(Patch) + sizeof(PartData);
    case PARAMETER_LEVEL_MULTI:
      return sizeof(MultiData);
    case PARAMETER_LEVEL_SYSTEM:
      return sizeof(SystemSettingsData);
  }
  return 256;  // UI state: not checked
}

}  // namespace

TEST(ParameterPartLayoutIsContiguous) {
  // Part::SetValue/GetValue index part bytes from &patch_: patch and part
  // data must be adjacent.
  native_env::Boot();
  CHECK(multi.part(0).raw_patch_data() + sizeof(Patch) ==
        multi.part(0).raw_data());
  CHECK_EQ(PRM_PART_SPREAD_MODE, sizeof(Patch) + offsetof(PartData,
                                                          spread_mode));
}

TEST(ParameterRangesAndOffsetsAreSane) {
  for (uint8_t i = 0; i < kNumParameters; ++i) {
    const Parameter& p = parameter_manager.parameter(i);
    CHECK_MSG(Signed(p, p.min_value) <= Signed(p, p.max_value),
              "parameter %d: min %d > max %d", i, Signed(p, p.min_value),
              Signed(p, p.max_value));
    CHECK_MSG(p.num_instances >= 1, "parameter %d has no instance", i);
    if (p.level == PARAMETER_LEVEL_UI) continue;
    size_t last = p.offset + p.stride * (p.num_instances - 1);
    CHECK_MSG(last < LevelSize(p), "parameter %d: last byte %d outside %d",
              i, (int)last, (int)LevelSize(p));
    if (p.level == PARAMETER_LEVEL_PATCH) {
      CHECK_MSG(last < sizeof(Patch), "patch parameter %d at %d", i,
                (int)last);
    }
    if (p.level == PARAMETER_LEVEL_PART) {
      CHECK_MSG(p.offset >= sizeof(Patch), "part parameter %d at %d", i,
                p.offset);
    }
  }
}

TEST(ParameterNrpnMapPointsAtTheRightBytes) {
  // Every NRPN address that maps to a parameter must be one of that
  // parameter's instances; otherwise an NRPN write lands on the wrong byte.
  int mapped = 0;
  for (int address = 0; address < 256; ++address) {
    uint8_t id = parameter_manager.AddressToParameterId(address);
    if (id == 0xff) continue;
    ++mapped;
    // 0xfe: raw byte (sequencer data), see ParameterManager::parameter().
    if (id == 0xfe) {
      CHECK_MSG(address >= PRM_PART_VOLUME, "NRPN %d -> raw byte", address);
      continue;
    }
    CHECK_MSG(id < kNumParameters, "NRPN %d -> bad id %d", address, id);
    const Parameter& p = parameter_manager.parameter(id);
    CHECK_MSG(p.level <= PARAMETER_LEVEL_PART, "NRPN %d -> level %d",
              address, p.level);
    bool hit = false;
    for (uint8_t k = 0; k < p.num_instances; ++k) {
      hit |= p.offset + p.stride * k == address;
    }
    CHECK_MSG(hit, "NRPN %d maps to parameter %d (offset %d stride %d x%d)",
              address, id, p.offset, p.stride, p.num_instances);
  }
  CHECK(mapped > 100);
}

TEST(ParameterEveryPatchByteHasAnNrpn) {
  // SHED and other editors write every patch byte by NRPN, except padding.
  for (uint8_t i = 0; i < kNumParameters; ++i) {
    const Parameter& p = parameter_manager.parameter(i);
    if (p.level != PARAMETER_LEVEL_PATCH) continue;
    for (uint8_t k = 0; k < p.num_instances; ++k) {
      uint8_t address = p.offset + p.stride * k;
      CHECK_MSG(parameter_manager.AddressToParameterId(address) == i,
                "patch parameter %d instance %d (byte %d) has no NRPN", i, k,
                address);
    }
  }
}

TEST(ParameterCcMapResolvesInstances) {
  for (int cc = 0; cc < 128; ++cc) {
    uint8_t id = parameter_manager.ControlChangeToParameterId(cc);
    if (id == 0xff) continue;
    CHECK_MSG(id < kNumParameters, "CC %d -> bad id %d", cc, id);
    const Parameter& p = parameter_manager.parameter(id);
    // Same search as Part::ControlChange.
    uint8_t controller = cc;
    uint8_t k;
    for (k = 0; k < p.num_instances; ++k) {
      if (p.midi_cc == controller) break;
      controller -= p.stride;
    }
    CHECK_MSG(k < p.num_instances,
              "CC %d -> parameter %d but no instance matches (cc %d stride %d)",
              cc, id, p.midi_cc, p.stride);
  }
}

TEST(ParameterClampScaleIncrementStayInRange) {
  for (uint8_t i = 0; i < kNumParameters; ++i) {
    Parameter p = parameter_manager.parameter(i);
    for (int v = 0; v < 256; ++v) {
      uint8_t c = p.Clamp(v);
      CHECK_MSG(InRange(p, c), "parameter %d: Clamp(%d) = %d", i, v, c);
      if (InRange(p, v)) {
        CHECK_MSG(c == v, "parameter %d: Clamp(%d) changed an in-range value",
                  i, v);
        static const int8_t steps[] = { 1, -1, 8, -8, 127, -128 };
        for (int s = 0; s < 6; ++s) {
          uint8_t n = p.Increment(v, steps[s]);
          CHECK_MSG(InRange(p, n), "parameter %d: Increment(%d, %d) = %d", i,
                    v, steps[s], n);
        }
      }
    }
    if (p.unit == UNIT_RAW_UINT8) continue;
    for (int v = 0; v < 128; ++v) {
      uint8_t s = p.Scale(v);
      CHECK_MSG(InRange(p, s), "parameter %d: Scale(%d) = %d", i, v, s);
    }
    CHECK_MSG(p.Scale(0) == p.min_value, "parameter %d: Scale(0) = %d", i,
              p.Scale(0));
  }
}

TEST(ParameterNrpnWritesAreClamped) {
  // Out-of-range NRPN values (data entry MSB set = 128..255) must be clamped
  // to the parameter's range before they reach the patch and the voicecards.
  native_env::Boot();
  for (int address = 0; address < 256; ++address) {
    uint8_t id = parameter_manager.AddressToParameterId(address);
    if (id == 0xff) continue;
    Parameter p = parameter_manager.parameter(id);
    if (address == PRM_PART_POLYPHONY_MODE) continue;  // reallocates voices
    for (int v = 0; v < 256; v += 17) {
      native_env::Nrpn(0, address, v);
      uint8_t stored = multi.part(0).raw_patch_data()[address];
      CHECK_MSG(InRange(p, stored), "NRPN %d value %d stored %d", address, v,
                stored);
    }
  }
}

TEST(ParameterNrpnPastThePartDataIsIgnored) {
  // Regression: midi_nrpn_map had 240 initializers for 256 entries, so NRPN
  // 240-255 mapped to parameter 0 and wrote past the part data.
  native_env::Boot();
  std::vector<uint8_t> before(multi.part(0).raw_patch_data(),
                              multi.part(0).raw_patch_data() + 256);
  for (int address = 196; address < 256; ++address) {
    native_env::Nrpn(0, address, 5);
  }
  native_env::Run(4);
  std::vector<uint8_t> after(multi.part(0).raw_patch_data(),
                             multi.part(0).raw_patch_data() + 256);
  for (int i = 0; i < 256; ++i) {
    CHECK_MSG(before[i] == after[i], "byte %d of the part changed", i);
  }
}
