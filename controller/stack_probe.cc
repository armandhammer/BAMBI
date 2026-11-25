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

#include "controller/stack_probe.h"

#include <avr/io.h>

// End of .bss/.noinit, provided by the avr-libc linker script.
extern uint8_t __heap_start;

static const uint8_t kStackPaint = 0xa5;

// Runs from .init3: the stack pointer is set (.init2) but nothing has been
// pushed yet, and .data/.bss are initialized afterwards (.init4), so it is
// safe to overwrite everything from __heap_start to RAMEND. Naked and without
// a return: execution falls through into the next init section.
extern "C" void StackProbePaint(void)
    __attribute__((naked, used, section(".init3")));

extern "C" void StackProbePaint(void) {
  uint8_t* p = &__heap_start;
  while (p <= reinterpret_cast<uint8_t*>(RAMEND)) {
    *p++ = kStackPaint;
  }
}

namespace ambika {

/* static */
uint16_t StackProbe::FreeBytes() {
  const uint8_t* start = &__heap_start;
  const uint8_t* p = start;
  while (p <= reinterpret_cast<const uint8_t*>(RAMEND) && *p == kStackPaint) {
    ++p;
  }
  return p - start;
}

}  // namespace ambika
