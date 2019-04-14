/**
* The MIT License (MIT)
* 
* Copyright (C) 2019  Seeed Technology Co.,Ltd. 
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include "Arduino.h"
#include "wiring_shift.h"

#ifdef __cplusplus
extern "C"{
#endif

uint32_t shiftIn(uint32_t ulDataPin, uint32_t ulClockPin, uint32_t ulBitOrder) {
	uint8_t value = 0;
	uint8_t i;

	for (i = 0; i < 8; ++i) {
		digitalWrite(ulClockPin, HIGH);

		if (ulBitOrder == LSBFIRST) {
			value |= digitalRead(ulDataPin) << i;
        } else {
			value |= digitalRead(ulDataPin) << (7 - i);
        }

		digitalWrite(ulClockPin, LOW) ;
	}

	return value ;
}

void shiftOut(uint32_t ulDataPin, uint32_t ulClockPin, uint32_t ulBitOrder, uint32_t ulVal) {
	uint8_t i ;

	for (i = 0 ; i < 8; i++) {
		if (ulBitOrder == LSBFIRST) {
			digitalWrite(ulDataPin, !!(ulVal & (1 << i)));
        } else {
			digitalWrite(ulDataPin, !!(ulVal & (1 << (7 - i))));
        }

		digitalWrite(ulClockPin, HIGH);
		digitalWrite(ulClockPin, LOW);		
	}
}

#ifdef __cplusplus
} // extern "C"

#endif
