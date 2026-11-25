#!/usr/bin/env python3
"""YAM+ Ambika SysEx client: query version, current locations, names, dumps.

Usage:
  python tools/yamplus_sysex.py --selftest          # offline framing test
  python tools/yamplus_sysex.py --list              # list MIDI ports
  python tools/yamplus_sysex.py --in "X" --out "Y" version
  python tools/yamplus_sysex.py --in "X" --out "Y" locations
  python tools/yamplus_sysex.py --in "X" --out "Y" name --part 1 --object program
  python tools/yamplus_sysex.py --in "X" --out "Y" dump --part 1 --object patch

Live use needs: pip install mido python-rtmidi

Frame (Mutable Instruments): F0 00 21 02 00 04 <cmd> <arg> <payload as
hi/lo nibbles> <checksum hi> <checksum lo> F7, checksum = sum(payload) & 0xff.
"""

import argparse
import sys
import time

HEADER = [0x00, 0x21, 0x02, 0x00, 0x04]  # MI manufacturer id + Ambika.
OBJECTS = {'patch': 0, 'sequence': 1, 'program': 2, 'multi': 3, 'part': 4}
FS_STATUS = {0: 'ok', 1: 'not ready', 2: 'error', 3: 'no file',
             4: 'no path', 5: 'bad name', 6: 'denied', 7: 'exists',
             8: 'eof', 9: 'bad format', 10: 'copy error', 11: 'timeout'}


def encode(command, argument=0, payload=()):
  """Returns the SysEx data bytes (without F0/F7, as mido expects)."""
  data = list(HEADER) + [command & 0x7f, argument & 0x7f]
  checksum = 0
  for byte in payload:
    data += [byte >> 4, byte & 0x0f]
    checksum = (checksum + byte) & 0xff
  data += [checksum >> 4, checksum & 0x0f]
  return data


def decode(data):
  """Parses SysEx data bytes (without F0/F7). Returns (cmd, arg, payload)."""
  data = list(data)
  if data[:5] != HEADER:
    raise ValueError('not an Ambika SysEx message')
  command, argument = data[5], data[6]
  nibbles = data[7:]
  if len(nibbles) % 2:
    raise ValueError('odd number of nibbles')
  raw = [(nibbles[i] << 4) | nibbles[i + 1] for i in range(0, len(nibbles), 2)]
  payload, checksum = raw[:-1], raw[-1]
  if sum(payload) & 0xff != checksum:
    raise ValueError('bad checksum')
  return command, argument, payload


def describe(command, argument, payload):
  if command == 0x0c:
    family, ctrl, yam, shapes, patch_layout, part_layout = payload[:6]
    lines = ['family %s, controller v%x.%x, YAM+ %d.%d' % (
        'YAM+' if family == 1 else family, ctrl >> 4, ctrl & 15,
        yam >> 4, yam & 15),
        'oscillator shapes: %d, patch layout %d, part layout %d' % (
            shapes, patch_layout, part_layout)]
    for port in range(6):
      slave, version = payload[6 + 2 * port], payload[7 + 2 * port]
      present = 0 < slave < 0xff
      lines.append('  port %d: %s' % (port + 1, (
          'voicecard v%x.%x' % (version >> 4, version & 15))
          if present else 'empty'))
    return '\n'.join(lines)
  if command == 0x0a:
    words = [payload[i] | (payload[i + 1] << 8)
             for i in range(0, len(payload), 2)]
    lines = []
    for part in range(6):
      cells = []
      for k, label in enumerate(('patch', 'seq', 'program')):
        w = words[part * 3 + k]
        cells.append('%s %s-%03d' % (label, chr(65 + (w >> 8)), w & 0xff))
      lines.append('  part %d: %s' % (part + 1, ', '.join(cells)))
    w = words[18]
    lines.append('  multi: %s-%03d' % (chr(65 + (w >> 8)), w & 0xff))
    return '\n'.join(lines)
  if command == 0x06:
    obj, bank, slot, status = payload[:4]
    name = ''.join(chr(c) for c in payload[4:20]).rstrip()
    kind = [k for k, v in OBJECTS.items() if v == obj]
    return '%s (part %s) %s-%03d: "%s" [%s]' % (
        kind[0] if kind else obj, argument or '-', chr(65 + bank), slot,
        name, FS_STATUS.get(status, status))
  if 1 <= command <= 5:
    return 'object %d dump, argument %d (part), %d bytes' % (
        command, argument, len(payload))
  return 'command 0x%02x, argument %d, %d bytes' % (
      command, argument, len(payload))


def selftest():
  # Round trip, including bytes with the high bit set.
  payload = [0, 1, 0x7f, 0x80, 0xff, 0x55]
  cmd, arg, out = decode(encode(0x01, 3, payload))
  assert (cmd, arg, out) == (0x01, 3, payload), (cmd, arg, out)
  # Requests carry an empty payload and a 00 00 checksum, like Ixox sends.
  assert encode(0x11, 0) == HEADER + [0x11, 0x00, 0x00, 0x00]
  # Name request: 1 byte payload.
  assert encode(0x16, 1, [2]) == HEADER + [0x16, 1, 0, 2, 0, 2]
  # A version reply as the firmware would build it.
  reply = [1, 0x10, 0x01, 43, 1, 1] + [1, 0x10] * 5 + [0xff, 0xff]
  text = describe(*decode(encode(0x0c, 0, reply)))
  assert 'YAM+ 0.1' in text and 'port 6: empty' in text, text
  # A name reply.
  name = [ord(c) for c in 'BRASS PAD       ']
  text = describe(*decode(encode(0x06, 2, [2, 0, 7, 0] + name)))
  assert '"BRASS PAD"' in text and 'A-007' in text, text
  # Corruption is detected.
  bad = encode(0x01, 0, [1, 2, 3])
  bad[-1] ^= 1
  try:
    decode(bad)
    raise AssertionError('checksum not checked')
  except ValueError:
    pass
  print('selftest: ok')


def main():
  parser = argparse.ArgumentParser(description=__doc__.split('\n')[0])
  parser.add_argument('request', nargs='?',
                      choices=['version', 'locations', 'name', 'dump'])
  parser.add_argument('--in', dest='inport')
  parser.add_argument('--out', dest='outport')
  parser.add_argument('--part', type=int, default=0,
                      help='1-6, 0 = active part')
  parser.add_argument('--object', choices=sorted(OBJECTS), default='program')
  parser.add_argument('--selftest', action='store_true')
  parser.add_argument('--list', action='store_true')
  args = parser.parse_args()

  if args.selftest:
    selftest()
    return
  import mido  # Only needed for live use.
  if args.list:
    print('inputs: ', mido.get_input_names())
    print('outputs:', mido.get_output_names())
    return
  if not (args.request and args.inport and args.outport):
    parser.error('request, --in and --out are required')

  obj = OBJECTS[args.object]
  if args.request == 'version':
    data = encode(0x1c)
  elif args.request == 'locations':
    data = encode(0x1a)
  elif args.request == 'name':
    data = encode(0x16, args.part, [obj])
  else:
    data = encode(0x11 + obj, args.part)

  with mido.open_input(args.inport) as inp, mido.open_output(args.outport) as out:
    out.send(mido.Message('sysex', data=data))
    deadline = time.time() + 3.0
    while time.time() < deadline:
      for msg in inp.iter_pending():
        if msg.type != 'sysex':
          continue
        try:
          print(describe(*decode(msg.data)))
        except ValueError as e:
          print('ignored message:', e)
      time.sleep(0.01)


if __name__ == '__main__':
  sys.exit(main())
