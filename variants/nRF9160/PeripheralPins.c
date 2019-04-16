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
	{P0_17, DT_SPI_3_LABEL, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_SPI_MOSI[] = {
	{P0_18, DT_SPI_3_LABEL, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_SPI_SCLK[] = {
	{P0_19, DT_SPI_3_LABEL, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_I2C_SDA[] = {
	{P0_30, DT_I2C_2_LABEL, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_I2C_SCL[] = {
	{P0_31, DT_I2C_2_LABEL, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_UART_TX[] = {
	{P0_29, DT_UART_0_LABEL, INVALID},
	{P0_01, DT_UART_1_LABEL, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_UART_RX[] = {
	{P0_28, DT_UART_0_LABEL, INVALID},
	{P0_00, DT_UART_1_LABEL, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_UART_RTS[] = {
	{P0_27, DT_UART_0_LABEL, INVALID},
	{P0_14, DT_UART_1_LABEL, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_UART_CTS[] = {
	{P0_26, DT_UART_0_LABEL, INVALID},
	{P0_15, DT_UART_1_LABEL, INVALID},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_PWM[] = {
	{P0_02, DT_PWM_0_LABEL, PWM0_0},
	{NC, NP, INVALID},
};

PeripheralPinMap PinMap_ADC[] = {
	{P0_13, DT_ADC_0_LABEL, ADC_AIN0},
	{P0_14, DT_ADC_0_LABEL, ADC_AIN1},
	{P0_15, DT_ADC_0_LABEL, ADC_AIN2},
	{P0_16, DT_ADC_0_LABEL, ADC_AIN3},
	{P0_17, DT_ADC_0_LABEL, ADC_AIN4},
	{P0_18, DT_ADC_0_LABEL, ADC_AIN5},
	{P0_19, DT_ADC_0_LABEL, ADC_AIN6},
	{P0_20, DT_ADC_0_LABEL, ADC_AIN7},
	{NC, NP, INVALID},
};

uint8_t pin_in_PeripheralPinMap(uint32_t pin, PeripheralPinMap *peripheralPinMap) {
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
