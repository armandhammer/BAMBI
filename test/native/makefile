# Native (host) unit tests for the BAMBI firmware.
#
# Run from the repository root on Linux (or via test/native/run.sh, which
# uses Docker image gcc:14 on Windows/macOS):
#   make -f test/native/makefile          # build and run everything
#   make -f test/native/makefile TEST=Env # only tests whose name contains Env
#
# The firmware sources are compiled unmodified with the host g++ against the
# shims in test/native/shim (fake AVR registers, EEPROM, PROGMEM). A few
# headers that busy-wait on interrupt-driven buffers, and avrlib/op.h (whose
# AVR assembly versions can't build on x86, and whose C fallback for U24Sub
# doesn't compile), are copied into $(BUILD)/override with a sed patch, so
# the avrlib submodule stays pristine.

BUILD    ?= build/native
CXX      ?= g++
CC       ?= gcc
OPT      ?= -O1
COMMON   := $(OPT) -g -w -fshort-enums -ffunction-sections -fdata-sections \
            -DNATIVE_HOST_BUILD \
            -D__PROG_TYPES_COMPAT__ -DF_CPU=20000000L \
            -include test/native/harness/native_hooks.h
# SANITIZE=1: AddressSanitizer (out-of-bounds table reads, overflows), in a
# separate build tree.
ifeq ($(SANITIZE),1)
COMMON   += -fsanitize=address -fno-omit-frame-pointer
LDFLAGS  += -fsanitize=address
BUILD    := $(BUILD)-asan
endif
OVR      := $(BUILD)/override
INCLUDES := -I$(OVR) -Itest/native/stubs -Itest/native/shim \
            -Itest/native/harness -I.
CXXFLAGS := -std=gnu++98 -fno-exceptions $(COMMON)
CFLAGS   := -std=gnu99 $(COMMON)

CTRL_DEFS := -D__AVR_ATmega644P__ -DATMEGA644P -DDISABLE_DEFAULT_UART_RX_ISR \
             -DMMC_CS_PORT=PORTB -DMMC_CS_BIT=4 -DMMC_NO_SPI_INITIALIZATION
VC_DEFS   := -D__AVR_ATmega328P__ -DATMEGA328P -DDISABLE_DEFAULT_UART_RX_ISR \
             -DDISABLE_WAVETABLE_LFOS -DSERIAL_RX_0

# FatFs is compiled from a copy of its directory (so its quoted includes
# find the patched integer.h), see the rules at the end.
FF_OVR    := $(patsubst avrlib/%,$(OVR)/avrlib/%,$(wildcard avrlib/third_party/ff/*))
OVERRIDES := $(OVR)/avrlib/op.h $(OVR)/avrlib/ring_buffer.h \
             $(OVR)/avrlib/avrlib.h $(OVR)/avrlib/devices/hd44780_lcd.h \
             $(OVR)/controller/midi_dispatcher.h $(FF_OVR)

# --- Controller test binary -------------------------------------------------
# Like the AVR link, the native one drops unreferenced sections
# (--gc-sections): some dead firmware functions call undefined ones.
# stack_probe.cc paints RAM up to RAMEND; the harness stubs it.
# voicecard_tx.cc busy-waits on its SPI buffers: built from a patched copy.
CTRL_FW_CC := $(filter-out controller/stack_probe.cc controller/voicecard_tx.cc, \
                $(wildcard avrlib/*.cc avrlib/filesystem/*.cc controller/*.cc \
                           controller/ui_pages/*.cc)) \
              $(OVR)/controller/voicecard_tx.cc
CTRL_FW_C  := $(filter %.c,$(FF_OVR))
CTRL_TESTS := $(wildcard test/native/tests/controller_*.cc)
CTRL_HARN  := test/native/harness/test_main.cc \
              test/native/harness/controller_env.cc
CTRL_SRCS  := $(CTRL_FW_CC) $(CTRL_FW_C) $(CTRL_TESTS) $(CTRL_HARN)
CTRL_OBJS  := $(patsubst %,$(BUILD)/ctrl/%.o,$(CTRL_SRCS))

# --- Voicecard test binary --------------------------------------------------
VC_GEN    := $(BUILD)/gen/voicecard_resources.cc
VC_FW_CC  := avrlib/random.cc voicecard/oscillator.cc voicecard/voice.cc \
             voicecard/audio_out.cc voicecard/load_probe.cc
VC_TESTS  := $(wildcard test/native/tests/voicecard_*.cc)
VC_HARN   := test/native/harness/test_main.cc \
             test/native/harness/voicecard_env.cc
VC_SRCS   := $(VC_FW_CC) $(VC_TESTS) $(VC_HARN)
VC_OBJS   := $(patsubst %,$(BUILD)/vc/%.o,$(VC_SRCS)) $(BUILD)/vc/gen.o

all: run

$(BUILD)/controller_tests: $(CTRL_OBJS)
	$(CXX) $(LDFLAGS) -Wl,--gc-sections -o $@ $^

$(BUILD)/voicecard_tests: $(VC_OBJS)
	$(CXX) $(LDFLAGS) -Wl,--gc-sections -o $@ $^

# The parameter table stores caption string ids on 8 bits: a caption with an
# id >= 256 would be truncated silently (the build uses -w). Compile it once
# more with that one warning as an error.
$(BUILD)/parameter_table.check: controller/parameter.cc controller/parameter.h \
                                controller/resources.h $(OVERRIDES)
	@mkdir -p $(dir $@)
	$(CXX) $(filter-out -w,$(CXXFLAGS)) -Werror=overflow $(CTRL_DEFS) \
	  $(INCLUDES) -fsyntax-only controller/parameter.cc 2> $@.log || \
	  { grep -A2 error $@.log; exit 1; }
	@touch $@

run: $(BUILD)/controller_tests $(BUILD)/voicecard_tests \
     $(BUILD)/parameter_table.check
	@echo "== controller"
	@$(BUILD)/controller_tests $(TEST)
	@echo "== voicecard"
	@$(BUILD)/voicecard_tests $(TEST)

# controller.cc holds the firmware main() and the timer ISRs.
$(BUILD)/ctrl/controller/controller.cc.o: CTRL_EXTRA := -Dmain=firmware_main
$(BUILD)/ctrl/%.cc.o: %.cc $(OVERRIDES)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CTRL_DEFS) $(CTRL_EXTRA) $(INCLUDES) -MMD -c $< -o $@

$(BUILD)/ctrl/$(OVR)/%.c.o: $(OVR)/%.c $(OVERRIDES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CTRL_DEFS) $(INCLUDES) -MMD -c $< -o $@

# FatFs's integer.h assumes a 16-bit int and 32-bit long, as on the AVR
# (avrlib/filesystem/file.cc passes uint16_t* where FatFs wants UINT*).
$(OVR)/avrlib/third_party/ff/integer.h: avrlib/third_party/ff/integer.h
	@mkdir -p $(dir $@)
	sed -e 's/^typedef int[[:space:]]*INT;/typedef short INT;/' \
	    -e 's/^typedef unsigned int[[:space:]]*UINT;/typedef unsigned short UINT;/' \
	    -e 's/^typedef long[[:space:]]*LONG;/typedef int LONG;/' \
	    -e 's/^typedef unsigned long[[:space:]]*ULONG;/typedef unsigned int ULONG;/' \
	    -e 's/^typedef unsigned long[[:space:]]*DWORD;/typedef unsigned int DWORD;/' \
	    $< > $@
	test "$$(grep -cE '^typedef (short INT|unsigned short UINT|int LONG|unsigned int ULONG|unsigned int DWORD);' $@)" = 5

$(OVR)/avrlib/third_party/ff/%: avrlib/third_party/ff/%
	@mkdir -p $(dir $@)
	cp $< $@

$(BUILD)/vc/%.cc.o: %.cc $(OVERRIDES)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(VC_DEFS) $(INCLUDES) -MMD -c $< -o $@

$(BUILD)/vc/gen.o: $(VC_GEN) $(OVERRIDES)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(VC_DEFS) $(INCLUDES) -MMD -c $< -o $@

# voicecard/resources.cc was generated on Windows:
# '#include "voicecard\resources.h"'.
$(VC_GEN): voicecard/resources.cc
	@mkdir -p $(dir $@)
	sed 's#voicecard\\resources.h#voicecard/resources.h#' $< > $@

# Generated header overrides. Each sed must change something: the check
# after it fails the build if upstream code moved.
$(OVR)/avrlib/op.h: avrlib/op.h
	@mkdir -p $(dir $@)
	sed -e '/^#define USE_OPTIMIZED_OP/d' 	    -e '/uint32_t difference = av - bv;/{n;s/sum >> 8/difference >> 8/;n;s/sum & 0xff/difference \& 0xff/;}' 	    $< > $@
	! grep -q '^#define USE_OPTIMIZED_OP' $@
	grep -q 'result.fractional = difference & 0xff' $@

$(OVR)/avrlib/ring_buffer.h: avrlib/ring_buffer.h
	@mkdir -p $(dir $@)
	sed -e 's/while (!writable());/while (!writable()) { AVRLIB_BUSY_WAIT(); }/' \
	    -e 's/while (!readable());/while (!readable()) { AVRLIB_BUSY_WAIT(); }/' \
	    $< > $@
	test "$$(grep -c AVRLIB_BUSY_WAIT $@)" = 2

# Non-void functions without a return statement: avr-gcc 4.3.5 returns
# garbage, but modern g++ treats reaching the end as unreachable and drops
# the code after the call. (BAMBI's own cases are fixed in the sources.)
$(OVR)/avrlib/avrlib.h: avrlib/avrlib.h
	@mkdir -p $(dir $@)
	sed 's/{ \*ptr() = value; }/{ *ptr() = value; return *this; }/' $< > $@
	test "$$(grep -c 'return \*this;' $@)" = 4

$(OVR)/avrlib/devices/hd44780_lcd.h: avrlib/devices/hd44780_lcd.h
	@mkdir -p $(dir $@)
	sed -e 's/static inline uint8_t Write(uint8_t character)/static inline void Write(uint8_t character)/' \
	    -e 's/static inline uint8_t Write(const char\* s)/static inline void Write(const char* s)/' \
	    $< > $@
	test "$$(grep -c 'static inline void Write(' $@)" = 2

$(OVR)/controller/voicecard_tx.cc: controller/voicecard_tx.cc
	@mkdir -p $(dir $@)
	sed 's/while (even_buffer_.readable() || odd_buffer_.readable());/while (even_buffer_.readable() || odd_buffer_.readable()) { AVRLIB_BUSY_WAIT(); }/' \
	    $< > $@
	grep -q AVRLIB_BUSY_WAIT $@

$(OVR)/controller/midi_dispatcher.h: controller/midi_dispatcher.h
	@mkdir -p $(dir $@)
	sed 's/while (OutputBufferLowPriority::readable());/while (OutputBufferLowPriority::readable()) { AVRLIB_BUSY_WAIT(); }/' \
	    $< > $@
	grep -q AVRLIB_BUSY_WAIT $@

clean:
	rm -rf $(BUILD)

.PHONY: all run clean
-include $(CTRL_OBJS:.o=.d) $(VC_OBJS:.o=.d)
