# Native firmware tests

The controller and voicecard firmware compiled for the host (x86-64 g++) and
driven by unit tests. They need no Ambika and no AVR simulator.

```sh
test/native/run.sh                 # build + run everything (Docker gcc:14 off Linux)
test/native/run.sh Envelope        # only tests whose name contains "Envelope"
make -f test/native/makefile SANITIZE=1   # same, with AddressSanitizer (Linux)
```

CI runs both the plain and the AddressSanitizer build on every push
(`.github/workflows/build.yml`, job `native-tests`).

## What runs

| Binary | Firmware linked | Harness |
|---|---|---|
| `controller_tests` | everything in `controller/`, `controller/ui_pages/`, `avrlib/` (incl. FatFs), except `stack_probe.cc` | `harness/controller_env.*`: a headless controller. MIDI bytes go into the real `MidiStreamParser`; MIDI out is drained from `midi_dispatcher`; every byte sent on the voicecard SPI bus is captured per voicecard |
| `voicecard_tests` | `voice.cc`, `oscillator.cc`, `audio_out.cc`, `load_probe.cc`, resources | `harness/voicecard_env.*`: renders `Voice::ProcessBlock()` into sample buffers |

Test files: `tests/controller_*.cc` and `tests/voicecard_*.cc` (picked up
by wildcard). The framework is `harness/test.h` (`TEST`, `CHECK`,
`CHECK_EQ`, `CHECK_NEAR`, `CHECK_MSG`); it is C++98 like the firmware.

## How the firmware compiles on a PC

- `shim/avr/*.h` replace avr-libc. `io.h` puts every special function
  register in a byte array (`native_sfr`); register names and bit numbers
  come from avr-libc 1.6.8's own `iom644p.h`/`iom328p.h` (BSD licence,
  copied into `shim/avr/libc/`). On the controller, `SPDR` is an object
  that logs writes, so the SPI traffic to the voicecards can be checked.
  `pgmspace.h` maps PROGMEM to ordinary memory, `eeprom.h` to a 4 KB array.
- `stubs/common/atomic.h` replaces the `cli`/`sei` assembly.
- The makefile copies a few headers into `build/native/override/` with a
  `sed` patch (the submodule stays pristine, and the build fails if a patch
  stops applying):
  - `avrlib/op.h`: use the C fallbacks instead of AVR assembly (and fix
    the fallback `U24Sub`, which doesn't compile upstream).
  - `avrlib/ring_buffer.h`, `controller/midi_dispatcher.h`,
    `controller/voicecard_tx.cc`: busy-wait loops call
    `AVRLIB_BUSY_WAIT()`, which runs the work the interrupts do on the
    hardware (drain MIDI out, send SPI bytes) and aborts on a real deadlock.
  - `avrlib/avrlib.h`, `avrlib/devices/hd44780_lcd.h`: add the missing
    `return` statements (see below).
  - FatFs: `integer.h` gets AVR-sized `INT`/`UINT`/`LONG`/`DWORD`.
- `voicecard/resources.cc` has `#include "voicecard\resources.h"`
  (generated on Windows); the makefile builds a fixed copy.
- Both binaries link with `--gc-sections`, like the AVR build: some dead
  firmware functions call functions that were never written.

## Things the native build is strict about

- **Non-void functions without `return`.** avr-gcc 4.3.5 just returns
  whatever is in r24. Modern g++ treats falling off the end as unreachable
  and silently drops the code that follows the call. The BAMBI sources are
  fixed. The upstream avrlib ones are patched in the override copies.
- **Memory layout.** Code that relied on how avr-gcc places variables
  (the voicecard used to write patch bytes through `patch_data_[address + 1]`)
  breaks here. BAMBI now writes through the struct.
- **Table bounds.** With `SANITIZE=1`, any read past a PROGMEM table fails.
  On the AVR the same read returns whatever flash follows the table.

## Limits

- `int` is 32-bit on the host, so 16-bit promotion and overflow details of
  the AVR are not reproduced. The C fallbacks of `avrlib/op.h` can round
  differently from the assembly versions by one LSB.
- Timing (ISR rates, SPI/UART speed) is not simulated: `Run(n)` calls the
  controller's Timer 2 interrupt (`multi.Tick()` + SPI send) `n` times and
  drains the buffers.
- The UI (LCD, switches, pots) and the SD card are not exercised.
