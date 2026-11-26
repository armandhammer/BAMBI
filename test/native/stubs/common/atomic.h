// Native stub for common/atomic.h: no interrupts on the host. (The real
// header emits a "cli" instruction, which is privileged on x86.)
#ifndef COMMON_ATOMIC_H_
#define COMMON_ATOMIC_H_
#include <avr/io.h>
#include "avrlib/base.h"
namespace ambika {
static inline uint8_t InterruptsOff() {
  uint8_t sreg = SREG;
  SREG = sreg & 0x7f;
  return sreg;
}
static inline void InterruptsRestore(uint8_t sreg) { SREG = sreg; }
}  // namespace ambika
#endif
