// Force-included into every native translation unit (see test/native/makefile).
//
// Firmware busy-waits on buffers that interrupts drain on the real hardware.
// The makefile generates copies of those headers in which each wait loop
// calls AVRLIB_BUSY_WAIT(); the harness uses it to run the simulated
// interrupt work (MIDI out drain) and to fail fast on a real deadlock.
#ifndef NATIVE_HARNESS_NATIVE_HOOKS_H_
#define NATIVE_HARNESS_NATIVE_HOOKS_H_
#ifdef __cplusplus
extern "C" {
#endif
void native_busy_wait(void);
#ifdef __cplusplus
}
#endif
#define AVRLIB_BUSY_WAIT() native_busy_wait()
#endif
