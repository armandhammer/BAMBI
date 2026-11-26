#include "voicecard_env.h"

#include <stdio.h>
#include <stdlib.h>

#include "voicecard/audio_out.h"
#include "voicecard/voice.h"

using namespace ambika;

extern "C" void native_busy_wait(void) {
  fprintf(stderr, "voicecard firmware busy-waited (no simulated ISR)\n");
  abort();
}

namespace native_vc {

void Reset(uint8_t index) {
  while (audio_buffer.readable()) audio_buffer.ImmediateRead();
  voice.Init();
  voice.set_voice_index(index);
  // On the hardware the block loop runs from power-on, so envelope phase
  // increments are computed before the first note. Envelopes latch their
  // increment at trigger time.
  voice.ProcessBlock();
  while (audio_buffer.readable()) audio_buffer.ImmediateRead();
}

void SetPatch(uint8_t address, uint8_t value) {
  voice.set_patch_data(address, value);
}

void SetPart(uint8_t address, uint8_t value) {
  voice.set_part_data(address, value);
}

void Render(int blocks, std::vector<uint8_t>* audio,
            std::vector<uint16_t>* cutoff, std::vector<uint8_t>* vca) {
  for (int b = 0; b < blocks; ++b) {
    voice.ProcessBlock();
    while (audio_buffer.readable()) {
      uint8_t s = audio_buffer.ImmediateRead();
      if (audio) audio->push_back(s);
    }
    if (cutoff) cutoff->push_back(voice.cutoff_cv());
    if (vca) vca->push_back(voice.vca());
  }
}

int PeakToPeak(const std::vector<uint8_t>& audio, size_t from, size_t size) {
  int lo = 255, hi = 0;
  for (size_t i = from; i < from + size && i < audio.size(); ++i) {
    if (audio[i] < lo) lo = audio[i];
    if (audio[i] > hi) hi = audio[i];
  }
  return hi >= lo ? hi - lo : 0;
}

}  // namespace native_vc
