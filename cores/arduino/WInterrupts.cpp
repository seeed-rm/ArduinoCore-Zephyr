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

#include <zephyr.h>
#include <gpio.h>

#include "Arduino.h"
#include "WInterrupts.h"

int gpio_configs[PinMap_Max] = {0};
static voidFuncPtr callbacks[PinMap_Max];

static void gpio_handler(struct device *port, struct gpio_callback *cb, u32_t pins) {
	int i = 0;
	
	for (i = 0; i < sizeof(gpio_configs)/sizeof(gpio_configs[0]); i++) {
		if (pins & (1 << i)) {
			if (NULL != callbacks[i]) {
				callbacks[i]();
			}
		}
	}
}

void attachInterrupt(uint32_t ulPin, void (*callback)(void), uint32_t ulMode) {
	int pinconf = 0;
	struct device *dev;

	if (ulPin < PinMap_Max) {
		if (0xf000 & gpio_configs[PinMap[ulPin].PinName]) {
			pinconf = GPIO_DIR_IN;
		} else {
			pinconf = gpio_configs[PinMap[ulPin].PinName];
		}
		
		switch (ulMode) {
			case LOW:
				pinconf |= (GPIO_INT_LEVEL | GPIO_INT_ACTIVE_LOW);
				break;
				
			case HIGH:
				pinconf |= (GPIO_INT_LEVEL | GPIO_INT_ACTIVE_HIGH);
				break;
				
			case CHANGE:
				pinconf |= (GPIO_INT_EDGE  | GPIO_INT_DOUBLE_EDGE);
				break;
				
			case FALLING:
				pinconf |= (GPIO_INT_EDGE  | GPIO_INT_ACTIVE_LOW);
				break;
				
			case RISING:
				pinconf |= (GPIO_INT_EDGE  | GPIO_INT_ACTIVE_HIGH);
				break;

			default:
				return;
		}
		gpio_configs[PinMap[ulPin].PinName] = pinconf;
		callbacks[PinMap[ulPin].PinName] = callback;
		dev = device_get_binding(DevLab[PinMap[ulPin].PioType]);
		if (NULL != dev) {
			gpio_pin_configure(dev, PinMap[ulPin].PinName, pinconf);
			gpio_init_callback(&gpio_cb[PinMap[ulPin].PinName], gpio_handler, BIT(PinMap[ulPin].PinName));
			gpio_add_callback(dev, &gpio_cb[PinMap[ulPin].PinName]);
			gpio_pin_enable_callback(dev, PinMap[ulPin].PinName);			
		}
	}
}

void detachInterrupt(uint32_t ulPin) {
	struct device *dev;

	if (ulPin < PinMap_Max) {
		dev = device_get_binding(DevLab[PinMap[ulPin].PioType]);
		if (NULL != dev) {
			gpio_remove_callback(dev, &gpio_cb[ulPin]);
			gpio_pin_disable_callback(dev, PinMap[ulPin].PinName);
		}
	}
}

