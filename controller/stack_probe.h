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
// Stack high-water probe. At reset, before .data/.bss are initialized, the
// RAM between the end of .bss (__heap_start; no heap is used) and RAMEND is
// filled with a known byte. StackProbe::FreeBytes() counts how many of those
// bytes, from the bottom up, have never been overwritten by the stack since
// boot: the worst-case stack headroom observed so far.

#ifndef CONTROLLER_STACK_PROBE_H_
#define CONTROLLER_STACK_PROBE_H_

#include "avrlib/base.h"

namespace ambika {

class StackProbe {
 public:
  static uint16_t FreeBytes();
};

}  // namespace ambika

#endif  // CONTROLLER_STACK_PROBE_H_
