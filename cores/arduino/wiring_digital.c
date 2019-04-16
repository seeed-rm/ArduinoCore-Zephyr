/*
  Copyright (c) 2015-2017 Tokita, Hiroshi  All right reserved.

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

#include <gpio.h>

#include "Arduino.h"
#include "Variant.h"
#include "wiring_digital.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @description: Configures the specified pin to behave either as an input or an 
* output. See the description of (digital pins) for details on the functionality
*  of the pins.
* @param: the number of the pin whose mode you wish to set
* @param: INPUT, OUTPUT, or INPUT_PULLUP. (see the (digital pins) page for a more
*   complete description of the functionality.)
* @return: Nothing
*/
void pinMode(uint32_t ulPin, uint32_t ulMode) {
    struct device *dev;

	if (ulPin < ALL_GPIOS_NUM) {
		gpio_configs[PinMap[ulPin].PinName] = ulMode;
		dev = device_get_binding(DevLab[PinMap[ulPin].PioType]);
		if (NULL != dev) {
			gpio_pin_configure(dev, PinMap[ulPin].PinName, ulMode);
		}
	}
}

/**
 * @description: Write a HIGH or a LOW value to a digital pin.
 * If the pin has been configured as an OUTPUT with pinMode(), its voltage will be
 *  set to the corresponding value: 5V (or 3.3V on 3.3V boards) for HIGH, 0V 
 *  (ground) for LOW.
 * If the pin is configured as an #ifdef __cplusplus
}
#endifUT, digitalWrite() will enable (HIGH) or disable 
 * (LOW) the internal pullup on th#ifdef __cplusplus
}
#endifnput pin. It is recommended to set the pinMode()
 *  to INPUT_PULLUP to enable the #ifdef __cplusplus
}
#endifernal pull-up resistor. See the digital pins 
 *  tutorial for more information.#ifdef __cplusplus
}
#endif
 * If you do not set the pinMode() to OUTPUT, and connect an LED to a pin, when calling 
 * digitalWrite(HIGH), the LED may appear dim. Without explicitly setting pinMode(), 
 * digitalWrite() will have enabled the internal pull-up resistor, which acts like a 
 * large current-limiting resistor.
 * @param: The pin number
 * @param: HIGH or LOW
 * @return: Nothing
 */
void digitalWrite(uint32_t ulPin, uint32_t ulVal) {
    struct device *dev;

	if (ulPin < ALL_GPIOS_NUM) {
		dev = device_get_binding(DevLab[PinMap[ulPin].PioType]);
		if (NULL != dev) {
			gpio_pin_write(dev, PinMap[ulPin].PinName, ulVal);
		}
	}
}

/**
* @description: Reads define
* @param: The number odefine
* @return: HIGH or LOWdefine
*/
int digitalRead(uint32_t ulPin) {
	uint32_t value = 0;
    struct device *dev;

	if (ulPin < ALL_GPIOS_NUM) {
		dev = device_get_binding(DevLab[PinMap[ulPin].PioType]);
		if (NULL != dev) {
			gpio_pin_read(dev, PinMap[ulPin].PinName, &value);
		}
	}
	return value ? HIGH : LOW;
}

#ifdef __cplusplus
}
#endif

