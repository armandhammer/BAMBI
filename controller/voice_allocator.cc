// Copyright 2011 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
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
// Polyphonic voice allocator.

#include "controller/voice_allocator.h"

#include <string.h>

#include "controller/part.h"

namespace ambika {
  
void VoiceAllocator::Clear() {
  ClearNotes();
  for (uint8_t i = 0; i < size_; ++i) {
    lru_[i] = size_ - i - 1;
  }
}

void VoiceAllocator::ClearNotes() {
  memset(pool_, 0, size_);
}

// BAMBI: rank of a note for stealing - the held note with the lowest rank
// loses its voice. All notes rank 0 in STEAL_OLDEST, so the scan below keeps
// the least recently played one, as in YAM.
static uint8_t StealRank(uint8_t note, uint8_t steal_mode) {
  if (steal_mode == STEAL_LOWEST) {
    return note;
  } else if (steal_mode == STEAL_HIGHEST) {
    return 0x7f - note;
  }
  return 0;
}

uint8_t VoiceAllocator::NoteOn(uint8_t note, uint8_t steal_mode) {
  if (size_ == 0) {
    return 0xff;
  }
  
  uint8_t voice;
  
  if (cyclic_allocator_ == 0xff) {
    // First, check if there is a voice currently playing this note. In this case
    // This voice will be responsible for retriggering this note.
    // Hint: if you're more into string instruments than keyboard instruments,
    // you can safely comment those lines.
    voice = Find(note);
  
    // Then, try to find the least recently touched, currently inactive voice.
    if (voice == 0xff) {
      for (uint8_t i = 0; i < size_; ++i) {
        if (lru_[i] < size_ && !(pool_[lru_[i]] & 0x80)) {
          voice = lru_[i];
        }
      }
    }
    // If all voices are active, steal one (BAMBI: see StealMode). lru_ runs
    // from the most to the least recently touched voice, so ties go to the
    // least recently played note.
    if (voice == 0xff) {
      if (steal_mode >= STEAL_NONE) {
        return 0xff;
      }
      uint8_t lowest_rank = 0xff;
      for (uint8_t i = 0; i < size_; ++i) {
        uint8_t candidate = lru_[i];
        if (candidate < size_) {
          uint8_t rank = StealRank(pool_[candidate] & 0x7f, steal_mode);
          if (rank <= lowest_rank) {
            lowest_rank = rank;
            voice = candidate;
          }
        }
      }
      // The new note would be the first one stolen: don't play it.
      if (StealRank(note, steal_mode) < lowest_rank) {
        return 0xff;
      }
    }
  } else {
    ++cyclic_allocator_;
    if (cyclic_allocator_ >= size_) {
      cyclic_allocator_ = 0;
    }
    voice = cyclic_allocator_;
  }
  
  pool_[voice] = 0x80 | note;
  Touch(voice);
  return voice;
}

uint8_t VoiceAllocator::Find(uint8_t note) const {
  for (uint8_t i = 0; i < size_; ++i) {
    if ((pool_[i] & 0x7f) == note) {
      return i;
    }
  }
  return 0xff;
}

uint8_t VoiceAllocator::FindActive(uint8_t note) const {
  for (uint8_t i = 0; i < size_; ++i) {
    if ((pool_[i] & 0x7f) == note && (pool_[i] & 0x80)) {
      return i;
    }
  }
  return 0xff;
}

uint8_t VoiceAllocator::NoteOff(uint8_t note) {
  uint8_t voice;
  if (cyclic_allocator_ == 0xff) {
    voice = Find(note);
    if (voice != 0xff) {
      pool_[voice] &= 0x7f;
      Touch(voice);
    }
  } else {
    // BAMBI fix: released cyclic slots used to be marked 0xff, which reads
    // as "active, note 127". Only an active slot can be released, and a
    // released one is cleared so it never matches a later note.
    voice = FindActive(note);
    if (voice != 0xff) {
      pool_[voice] = 0;
    }
  }
  return voice;
}

void VoiceAllocator::Touch(uint8_t voice) {
  int8_t source = size_ - 1;
  int8_t destination = size_ - 1;
  while (source >= 0) {
    if (lru_[source] != voice) {
      lru_[destination--] = lru_[source];
    }
    --source;
  }
  lru_[0] = voice;
}

}  // namespace ambika
