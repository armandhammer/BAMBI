// Headless Ambika controller: the real controller firmware, linked natively,
// with MIDI in/out and the voicecard SPI bus captured as byte streams.
//
//   native_env::Boot();                    // power-on with a blank EEPROM
//   native_env::MidiIn3(0x90, 60, 100);    // feed MIDI in
//   native_env::Run(10);                   // main loop + 10 control ticks
//   native_env::MidiOut();                 // bytes sent to MIDI out
//   native_env::VoicecardBytes(0);         // bytes sent to voicecard 0
#ifndef NATIVE_HARNESS_CONTROLLER_ENV_H_
#define NATIVE_HARNESS_CONTROLLER_ENV_H_

#include <inttypes.h>
#include <stddef.h>
#include <vector>

namespace native_env {

// Clears registers, EEPROM (all 0xff, like a new chip), the capture
// buffers, then runs the firmware's boot sequence minus the LCD/SD card.
void Boot();

// Feeds MIDI bytes to the firmware's MIDI parser (the main loop's job).
void MidiIn(const uint8_t* data, size_t size);
void MidiIn(const std::vector<uint8_t>& data);
void MidiIn3(uint8_t status, uint8_t a, uint8_t b);
void MidiIn2(uint8_t status, uint8_t a);
// NRPN write: CC 99/98 (address), then 6/38 (data entry MSB/LSB).
void Nrpn(uint8_t channel, uint16_t address, uint16_t value);

// Runs the Timer 2 interrupt (multi.Tick, SPI send) n times, each followed
// by the main loop's clock update.
void Run(int ticks);

// Everything the firmware put on its MIDI out buffers since the last
// ClearMidiOut(), drained in the order the UART would send it.
const std::vector<uint8_t>& MidiOut();
void ClearMidiOut();

// Every SPI byte sent to voicecard |voice| (0..5) since ClearSpi().
const std::vector<uint8_t>& VoicecardBytes(uint8_t voice);
void ClearSpi();

// Value a voicecard returns on the next SPI transfer (default 0).
void SetSpiReply(uint8_t value);

// How often firmware code busy-waited (each one ran the simulated ISRs).
unsigned long BusyWaits();

}  // namespace native_env

#endif  // NATIVE_HARNESS_CONTROLLER_ENV_H_
