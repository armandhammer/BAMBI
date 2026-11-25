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
// Critical sections for data shared with ISRs.
//
// avr-libc 1.6.8 defines cli() and sei() as asm statements without a
// "memory" clobber, so the compiler may move ordinary (non-volatile) loads
// and stores across them. These helpers add the compiler barrier.
//
//   uint8_t sreg = InterruptsOff();
//   ... access shared data ...
//   InterruptsRestore(sreg);

#ifndef COMMON_ATOMIC_H_
#define COMMON_ATOMIC_H_

#include <avr/io.h>

#include "avrlib/base.h"

namespace ambika {

static inline uint8_t InterruptsOff() {
  uint8_t sreg = SREG;
  __asm__ __volatile__ ("cli" ::: "memory");
  return sreg;
}

static inline void InterruptsRestore(uint8_t sreg) {
  __asm__ __volatile__ ("" ::: "memory");
  SREG = sreg;
}

}  // namespace ambika

#endif  // COMMON_ATOMIC_H_
