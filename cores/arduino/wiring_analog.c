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
#include "PinConfigured.h"

#ifdef __cplusplus
extern "C" {
#endif


static int _readResolution = 10;
static int _writeResolution = 8;

void analogReadResolution(int res) {
	_readResolution = res;
}

void analogWriteResolution(int res) {
	_writeResolution = res;
}

static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to) {
	if (from == to) {
		return value;
	}
	if (from > to) {
		return value >> (from-to);
	} else {
		return value << (to-from);
	}
}

//perform the read operation on the selected analog pin.
//the initialization of the analog PIN is done through this function
uint32_t analogRead(uint32_t ulPin) {
	uint32_t value;
	uint8_t adc_buffer[4] = {0};
	int ret = 0;
	
	struct device *dev;
	struct adc_channel_cfg adc_ch_cfg;
	struct adc_sequence adc_table;

	if (ulPin < PinMap_Max) {
		dev = device_get_binding(DevLab[PinMap[ulPin].PioType]);
		if (NULL != dev) {
			adc_ch_cfg.channel_id = 0;
			adc_ch_cfg.differential = false;
			adc_ch_cfg.gain = ADC_GAIN_1,
			adc_ch_cfg.reference = ADC_REF_INTERNAL;
			adc_ch_cfg.acquisition_time = ADC_ACQ_TIME_DEFAULT;

			adc_table.options = {
				.interval_us = 15,
				.callback = NULL,
				.extra_samplings = 0,
			};
			adc_table.buffer = adc_buffer;
			adc_table.resolution = _readResolution;
			adc_table.buffer_size = sizeof(adc_buffer) / sizeof(adc_buffer[0]);
			adc_table.channels = BIT(0);
			
			adc_channel_setup(dev, &adc_ch_cfg);

			ret = adc_read(dev, &adc_table);
			if (0 == ret) {
				value = (adc_buffer[3] << 24) | (adc_buffer[2] << 16) | (adc_buffer[1] << 8) | adc_buffer[0];
			}
		}
	}
	return value;
}

// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// variant.cpp file.  For the rest of the pins, we default
// to digital output.
void analogWrite(uint32_t ulPin, uint32_t ulValue) {
	uint16_t value;
	struct device *dev;

	if (ulPin < PinMap_Max) {
		if (PIO_ADC == PinMap[ulPin].PioType) {
			dev = device_get_binding(DevLab[PinMap[ulPin].PioType]);
			if (NULL != dev) {
				switch (_writeResolution) {
					case 8: // 8-bit
						value = (uint16_t)(ulValue * 10000 / 256);
						break;
				
					case 10: // 10-bit
						value = (uint16_t)(ulValue * 10000 / 1024);
						break;
				
					default:
						value = (uint16_t)(ulValue * 10000 / 4096);
						break;
				}
				pwm_pin_set_usec(dev, PinMap[ulPin].PinName, PERIOD, value);
			}
		} else {
			pinMode(ulPin, OUTPUT);
			if (ulValue > 0x7f) {
				digitalWrite(ulPin, HIGH);
			} else {
				digitalWrite(ulPin, LOW);
			}
		}
	}
}

#ifdef __cplusplus
}
#endif
