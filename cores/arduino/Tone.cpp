/*
  Copyright (c) 2017 Tokita, Hiroshi  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdint.h>
#include "wiring_digital.h"
#include "wiring_constants.h"


#ifndef TONE_INTERVAL_OFFSET
#define TONE_INTERVAL_OFFSET(f) 0
#endif

void tone(uint32_t _pin, uint32_t frequency, uint32_t duration) __attribute__((weak));
void noTone(uint32_t _pin) __attribute__((weak));

void tone(uint32_t pin, uint32_t frequency, uint32_t duration)
{
}

void noTone(uint32_t pin)
{
}

