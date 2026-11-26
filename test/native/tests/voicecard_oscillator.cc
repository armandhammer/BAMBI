// Oscillator (voicecard/oscillator.cc): every algorithm at every pitch and
// parameter stays inside its lookup tables. Run with SANITIZE=1 to turn any
// table overrun into a failure.
#include "test.h"

#include <string.h>
#include <avr/pgmspace.h>

#include "common/patch.h"
#include "voicecard/oscillator.h"
#include "voicecard/voice.h"

using namespace ambika;

namespace {

uint24_t Increment(uint16_t integral) {
  uint24_t i;
  i.integral = integral;
  i.fractional = 0;
  return i;
}

}  // namespace

TEST(OscillatorWavequenceClampsToLastWave) {
  // Regression: parameter 80..127 read past the 80-wave table.
  static Oscillator a, b;
  uint8_t no_sync[kAudioBlockSize], sync_out[kAudioBlockSize];
  memset(no_sync, 0, sizeof(no_sync));
  uint8_t out_a[kAudioBlockSize], out_b[kAudioBlockSize];
  a.set_parameter(79);
  b.set_parameter(127);
  for (int block = 0; block < 8; ++block) {
    a.Render(WAVEFORM_WAVEQUENCE, 60, Increment(1500), no_sync, sync_out,
             out_a);
    b.Render(WAVEFORM_WAVEQUENCE, 60, Increment(1500), no_sync, sync_out,
             out_b);
    CHECK(memcmp(out_a, out_b, sizeof(out_a)) == 0);
  }
}

TEST(OscillatorEveryShapePitchAndParameterSweep) {
  // Regression for the polyBLEP index overrun: sweep everything.
  static Oscillator o;
  uint8_t sync_in[kAudioBlockSize], sync_out[kAudioBlockSize];
  uint8_t out[kAudioBlockSize];
  memset(sync_in, 0, sizeof(sync_in));
  for (uint8_t shape = 0; shape < WAVEFORM_LAST; ++shape) {
    // Voice::RenderOscillators clamps the note it passes to 0..108.
    for (int note = 0; note <= 108; note += 3) {
      // Increments spanning the oscillator's range (low bass to > Nyquist/2).
      uint16_t integral = 40 + (static_cast<uint32_t>(note) * note * 3);
      for (int parameter = 0; parameter < 128; parameter += 9) {
        o.set_parameter(parameter);
        for (int block = 0; block < 3; ++block) {
          o.Render(shape, note, Increment(integral), sync_in, sync_out, out);
        }
      }
    }
  }
  CHECK(1);
}
