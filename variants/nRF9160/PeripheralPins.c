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
#include <stddef.h>

#include "Variant.h"
#include "PeripheralPins.h"

PeripheralPinMap PinMap_SPI_MISO[] = {
	{P0_17, DEV_SPI_3_STRING, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_SPI_MOSI[] = {
	{P0_18, DEV_SPI_3_STRING, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_SPI_SCLK[] = {
	{P0_19, DEV_SPI_3_STRING, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_I2C_SDA[] = {
	{P0_30, DEV_I2C_2_STRING, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_I2C_SCL[] = {
	{P0_31, DEV_I2C_2_STRING, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_UART_TX[] = {
	{P0_29, DEV_UART_0_STRING, INVALID},
	{P0_01, DEV_UART_1_STRING, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_UART_RX[] = {
	{P0_28, DEV_UART_0_STRING, INVALID},
	{P0_00, DEV_UART_1_STRING, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_UART_RTS[] = {
	{P0_27, DEV_UART_0_STRING, INVALID},
	{P0_14, DEV_UART_1_STRING, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_UART_CTS[] = {
	{P0_26, DEV_UART_0_STRING, INVALID},
	{P0_15, DEV_UART_1_STRING, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_PWM[] = {
	{P0_02, DEV_PWM_0_STRING, PWM0_0},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_ADC[] = {
	{P0_13, DEV_ADC_0_STRING, ADC_AIN0},
	{P0_14, DEV_ADC_0_STRING, ADC_AIN1},
	{P0_15, DEV_ADC_0_STRING, ADC_AIN2},
	{P0_16, DEV_ADC_0_STRING, ADC_AIN3},
	{P0_17, DEV_ADC_0_STRING, ADC_AIN4},
	{P0_18, DEV_ADC_0_STRING, ADC_AIN5},
	{P0_19, DEV_ADC_0_STRING, ADC_AIN6},
	{P0_20, DEV_ADC_0_STRING, ADC_AIN7},
	{NC, NP, INVALID},
};

bool pin_in_PeripheralPinMap(uint32_t pin, PeripheralPinMap *peripheralPinMap) {
    if ((NC != pin) && (NULL != peripheralPinMap)) {
        while (NC != peripheralPinMap->PinName) {
            if (pin == peripheralPinMap->PinName) {
                return true;
            }
			peripheralPinMap++;
        }
    }
	return false;
}

uint8_t get_peripheralPinMap_index(uint32_t pin, PeripheralPinMap *peripheralPinMap) {
    uint8_t i = 0;

    if ((NC != pin) && (NULL != peripheralPinMap)) {
        while (NC != peripheralPinMap->PinName) {
            if (pin == peripheralPinMap->PinName) {
                return i;
            }
			i++;
			peripheralPinMap++;
        }
    }
    return 0xff;
}
