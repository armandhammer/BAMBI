// Parameter captions and value texts, against a golden copy taken from YAM+
// 0.3 (BAMBI PR #3) before the parameter table stored its string ids on 8
// bits. Any change to the string table (an inserted string that shifts a
// value list, a duplicate that steals an id) or to a parameter's names shows
// up here.
//
// Regenerate (only when a caption change is intended):
//   DUMP_PARAMETER_NAMES=1 test/native/run.sh ParameterNames
// and paste the printed rows into parameter_names_golden.h.
#include "test.h"
#include "controller_env.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "controller/parameter.h"
#include "controller/resources.h"

using namespace ambika;

namespace {

struct GoldenRow {
  const char* short_name;
  const char* long_name;
  const char* object;
  unsigned long values_hash;  // FNV-1a over every value's printed text.
};

#include "parameter_names_golden.h"

void Load(ResourceId id, char* buffer) {
  memset(buffer, 0, 41);
  ResourcesManager::LoadStringResource(id, buffer, 40);
  buffer[40] = '\0';
}

unsigned long ValuesHash(const Parameter& p) {
  unsigned long h = 2166136261UL;
  uint8_t v = p.min_value;
  while (true) {
    char buffer[16];
    memset(buffer, 0, sizeof(buffer));
    p.PrintValue(v, buffer, 6);
    for (uint8_t i = 0; i < 6; ++i) {
      h = ((h ^ static_cast<uint8_t>(buffer[i])) * 16777619UL) & 0xffffffffUL;
    }
    if (v == p.max_value) break;
    ++v;
  }
  return h;
}

}  // namespace

TEST(ParameterNamesMatchGolden) {
  native_env::Boot();
  bool dump = getenv("DUMP_PARAMETER_NAMES") != NULL;
  const uint8_t num_golden = sizeof(kGoldenNames) / sizeof(kGoldenNames[0]);
  CHECK(kNumParameters >= num_golden);
  for (uint8_t i = 0; i < (dump ? kNumParameters : num_golden); ++i) {
    const Parameter& p = parameter_manager.parameter(i);
    char s[41], l[41], o[41];
    Load(p.short_name, s);
    Load(p.long_name, l);
    Load(p.object, o);
    unsigned long h = ValuesHash(p);
    if (dump) {
      printf("  { \"%s\", \"%s\", \"%s\", 0x%08lxUL },  // %d\n", s, l, o, h,
             i);
      continue;
    }
    const GoldenRow& g = kGoldenNames[i];
    CHECK_MSG(!strcmp(s, g.short_name), "parameter %d short name '%s' != '%s'",
              i, s, g.short_name);
    CHECK_MSG(!strcmp(l, g.long_name), "parameter %d long name '%s' != '%s'",
              i, l, g.long_name);
    CHECK_MSG(!strcmp(o, g.object), "parameter %d object '%s' != '%s'", i, o,
              g.object);
    CHECK_MSG(h == g.values_hash, "parameter %d value texts changed", i);
  }
}
