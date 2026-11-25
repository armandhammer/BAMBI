// Copyright 2026 YAM+ contributors.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// CPU load measurement, read by the controller over SPI.
//
// peak_block_samples: the largest number of samples the audio ISR played while
// the main loop was computing one block of kAudioBlockSize samples. Time is
// measured in sample periods, so ISR time is included. 40 = 100% load; the
// audio buffer absorbs short overruns, sustained values above 40 underrun.
//
// underruns: number of times the ISR found the audio buffer empty, saturating
// at 255. Should stay at 0.
//
// Both values are peak-hold since boot or since the last
// COMMAND_CLEAR_LOAD_PROBE.

#ifndef VOICECARD_LOAD_PROBE_H_
#define VOICECARD_LOAD_PROBE_H_

#include "avrlib/base.h"

namespace ambika {

struct LoadProbe {
  static volatile uint8_t peak_block_samples;
  static volatile uint8_t underruns;

  static inline void Clear() {
    peak_block_samples = 0;
    underruns = 0;
  }
};

}  // namespace ambika

#endif  // VOICECARD_LOAD_PROBE_H_
