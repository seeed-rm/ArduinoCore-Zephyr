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

#ifndef PeripheralPins_h
#define PeripheralPins_h

#include <stddef.h>
#include "nrf_saadc.h"

#define ADC_AIN0	SAADC_CH_PSELP_PSELP_AnalogInput1
#define ADC_AIN1	SAADC_CH_PSELP_PSELP_AnalogInput2
#define ADC_AIN2	SAADC_CH_PSELP_PSELP_AnalogInput4
#define ADC_AIN3	SAADC_CH_PSELP_PSELP_AnalogInput5
#define ADC_AIN4	SAADC_CH_PSELP_PSELP_AnalogInput6
#define ADC_AIN5	SAADC_CH_PSELP_PSELP_AnalogInput7
#define ADC_AIN6	SAADC_CH_PSELP_PSELP_AnalogInput0
#define ADC_AIN7	SAADC_CH_PSELP_PSELP_AnalogInput3

// Definitions for PWM channels
// MSB = PWM module (0 - NRF_PWM0, 1 - NRF_PWM1, 2 - NRF_PWM2)
// LSB = PWM channel (0 to 3)
// ex: 0x10 = PWM1 channel 0
#define PWM0_0		(0x00)
#define PWM0_1		(0x01)
#define PWM0_2		(0x02)
#define PWM0_3		(0x02)
#define PWM1_0		(0x10)
#define PWM1_1		(0x11)
#define PWM1_2		(0x12)
#define PWM1_3		(0x13)
#define PWM2_0		(0x20)
#define PWM2_1		(0x21)
#define PWM2_2		(0x22)
#define PWM2_3		(0x23)

#define INVALID		(0xffffffff)
#define NP			(void *)0

typedef struct _PeripheralPinMap {
	uint32_t PinName;
	char *dev;
	uint32_t channel; // pwm or adc channel
} PeripheralPinMap;


extern PeripheralPinMap PinMap_SPI_MISO[];
extern PeripheralPinMap PinMap_SPI_MOSI[];
extern PeripheralPinMap PinMap_SPI_SCLK[];
extern PeripheralPinMap PinMap_I2C_SDA[];
extern PeripheralPinMap PinMap_I2C_SCL[];
extern PeripheralPinMap PinMap_UART_TX[];
extern PeripheralPinMap PinMap_UART_RX[];
extern PeripheralPinMap PinMap_UART_RTS[];
extern PeripheralPinMap PinMap_UART_CTS[];
extern PeripheralPinMap PinMap_PWM[];
extern PeripheralPinMap PinMap_ADC[];

extern bool pin_in_PeripheralPinMap(uint32_t pin, PeripheralPinMap *peripheralPinMap);
extern uint8_t get_peripheralPinMap_index(uint32_t pin, PeripheralPinMap *peripheralPinMap);
#endif // PeripheralPins_h