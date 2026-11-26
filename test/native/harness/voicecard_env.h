// Headless voicecard: the real Voice DSP code rendering into a buffer.
#ifndef NATIVE_HARNESS_VOICECARD_ENV_H_
#define NATIVE_HARNESS_VOICECARD_ENV_H_

#include <inttypes.h>
#include <stddef.h>
#include <vector>

namespace native_vc {

// Voice::Init() with the default patch, voice slot |index|.
void Reset(uint8_t index = 0);

// Writes one patch byte the way the controller does (COMMAND_WRITE_PATCH_DATA).
void SetPatch(uint8_t address, uint8_t value);
// Writes one part byte (COMMAND_WRITE_PART_DATA).
void SetPart(uint8_t address, uint8_t value);

// Renders |blocks| control-rate blocks (40 samples each). Appends audio
// samples (unsigned 8-bit, 128 = silence) to |audio| if given, and the
// per-block cutoff / VCA CVs to the optional vectors.
void Render(int blocks, std::vector<uint8_t>* audio = 0,
            std::vector<uint16_t>* cutoff = 0, std::vector<uint8_t>* vca = 0);

// Peak-to-peak amplitude of a block of samples.
int PeakToPeak(const std::vector<uint8_t>& audio, size_t from, size_t size);

}  // namespace native_vc

#endif  // NATIVE_HARNESS_VOICECARD_ENV_H_
