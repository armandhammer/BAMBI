#include "controller_env.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "controller/midi_dispatcher.h"
#include "controller/multi.h"
#include "controller/stack_probe.h"
#include "controller/system_settings.h"
#include "controller/voicecard_tx.h"
#include "midi/midi.h"

using namespace ambika;

// Globals and ISRs defined in controller/controller.cc.
extern midi::MidiStreamParser<MidiDispatcher> midi_parser;
extern "C" void TIMER2_OVF_vect(void);

extern uint8_t native_eeprom[E2END + 1];

NativeSpdr native_spdr;

namespace ambika {
// stack_probe.cc is not linked (it paints RAM up to RAMEND).
uint16_t StackProbe::FreeBytes() { return 1024; }
}

namespace native_env {

static std::vector<uint8_t> midi_out;
static std::vector<uint8_t> spi_bytes[8];
static uint8_t spi_reply = 0;
static unsigned long busy_waits = 0;
static unsigned long busy_waits_without_progress = 0;

static bool DrainMidiOut() {
  bool progress = false;
  while (midi_dispatcher.readable_high_priority()) {
    midi_out.push_back(midi_dispatcher.ImmediateReadHighPriority());
    progress = true;
  }
  while (midi_dispatcher.readable_low_priority()) {
    midi_out.push_back(midi_dispatcher.ImmediateReadLowPriority());
    progress = true;
  }
  return progress;
}

static size_t SpiTotal() {
  size_t n = 0;
  for (int i = 0; i < 8; ++i) n += spi_bytes[i].size();
  return n;
}

void Boot() {
  memset((void*)native_sfr, 0, sizeof(native_sfr));
  SREG = 0x80;
  SPSR |= _BV(SPIF);      // every SPI transfer completes immediately
  UCSR0A |= _BV(UDRE0);   // UART always ready to send
  memset(native_eeprom, 0xff, sizeof(native_eeprom));
  midi_out.clear();
  ClearSpi();
  spi_reply = 0;
  busy_waits = 0;
  busy_waits_without_progress = 0;
  // Leftovers in the static ring buffers from a previous test.
  DrainMidiOut();
  midi_out.clear();
  // controller.cc Init(), minus the UI (LCD, switches) and the SD card.
  system_settings.Init(false);
  voicecard_tx.Init();
  voicecard_tx.SyncAllVoices();
  multi.Init(false);
  Run(4);
  midi_out.clear();
  ClearSpi();
}

void MidiIn(const uint8_t* data, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    midi_parser.PushByte(data[i]);
  }
}

void MidiIn(const std::vector<uint8_t>& data) {
  if (!data.empty()) MidiIn(&data[0], data.size());
}

void MidiIn3(uint8_t status, uint8_t a, uint8_t b) {
  uint8_t m[3] = { status, a, b };
  MidiIn(m, 3);
}

void MidiIn2(uint8_t status, uint8_t a) {
  uint8_t m[2] = { status, a };
  MidiIn(m, 2);
}

void Nrpn(uint8_t channel, uint16_t address, uint16_t value) {
  uint8_t cc = 0xb0 | (channel & 0x0f);
  MidiIn3(cc, 99, (address >> 7) & 0x7f);
  MidiIn3(cc, 98, address & 0x7f);
  MidiIn3(cc, 6, (value >> 7) & 0x7f);
  MidiIn3(cc, 38, value & 0x7f);
}

void Run(int ticks) {
  for (int i = 0; i < ticks; ++i) {
    TIMER2_OVF_vect();
    multi.UpdateClocks();
    DrainMidiOut();
  }
  // Let the SPI buffers empty, as they would within a few more ticks.
  for (int i = 0; i < 128; ++i) {
    voicecard_tx.SendBytes();
  }
  DrainMidiOut();
}

const std::vector<uint8_t>& MidiOut() {
  DrainMidiOut();
  return midi_out;
}

void ClearMidiOut() {
  DrainMidiOut();
  midi_out.clear();
}

const std::vector<uint8_t>& VoicecardBytes(uint8_t voice) {
  return spi_bytes[voice & 7];
}

void ClearSpi() {
  for (int i = 0; i < 8; ++i) spi_bytes[i].clear();
}

void SetSpiReply(uint8_t value) { spi_reply = value; }

unsigned long BusyWaits() { return busy_waits; }

uint8_t CurrentSpiReply() { return spi_reply; }

void LogSpi(uint8_t value) {
  spi_bytes[PORTB & 0x07].push_back(value);
}

}  // namespace native_env

NativeSpdr& NativeSpdr::operator=(uint8_t value) {
  native_env::LogSpi(value);
  return *this;
}

NativeSpdr::operator uint8_t() const {
  return native_env::CurrentSpiReply();
}

// Firmware is waiting for an interrupt to drain a buffer: be that interrupt.
extern "C" void native_busy_wait(void) {
  using namespace native_env;
  ++busy_waits;
  size_t before = midi_out.size() + SpiTotal();
  DrainMidiOut();
  voicecard_tx.SendBytes();
  if (midi_out.size() + SpiTotal() != before) {
    busy_waits_without_progress = 0;
    return;
  }
  if (++busy_waits_without_progress > 100000) {
    fprintf(stderr, "native_busy_wait: firmware is stuck in a busy-wait loop "
            "that no simulated interrupt can release\n");
    abort();
  }
}
