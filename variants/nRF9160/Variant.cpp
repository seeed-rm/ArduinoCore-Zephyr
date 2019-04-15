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

#include "Variant.h"

const char * DevLab[] = {
	DEV_GPIO_0_STRING,
	DEV_SPI_0_STRING,
	DEV_SPI_1_STRING,
	DEV_SPI_2_STRING,
	DEV_SPI_3_STRING,
	DEV_I2C_0_STRING,
	DEV_I2C_1_STRING,
	DEV_I2C_2_STRING,
	DEV_I2C_3_STRING,
	DEV_UART_0_STRING,
	DEV_UART_1_STRING,
	DEV_UART_2_STRING,
	DEV_UART_3_STRING,
	DEV_I2S_STRING,
	DEV_PWM_0_STRING,
	DEV_PWM_1_STRING,
	DEV_PWM_2_STRING,
	DEV_ADC_0_STRING,
};

const PinDescription PinMap[PinMap_Max] = {
	{P0_00, PIO_UART_1},
	{P0_01, PIO_UART_1},
	{P0_02, PIO_PWM_0},//PIO_GPIO_0},
	{P0_03, PIO_GPIO_0},
	{P0_04, PIO_GPIO_0},
	{P0_05, PIO_GPIO_0},
	{P0_06, PIO_GPIO_0},
	{P0_07, PIO_GPIO_0},
	{P0_08, PIO_GPIO_0},
	{P0_09, PIO_GPIO_0},
	{P0_10, PIO_UART_0},
	{P0_11, PIO_UART_0},
	{P0_12, PIO_GPIO_0},
	{P0_13, PIO_GPIO_0},
	{P0_14, PIO_UART_1},
	{P0_15, PIO_UART_1},
	{P0_16, PIO_GPIO_0},
	{P0_17, PIO_SPI_3},
	{P0_18, PIO_SPI_3},
	{P0_19, PIO_SPI_3},
	{P0_20, PIO_UART_0},
	{P0_21, PIO_UART_0},
	{P0_22, PIO_GPIO_0},
	{P0_23, PIO_GPIO_0},
	{P0_24, PIO_GPIO_0},
	{P0_25, PIO_GPIO_0},
	{P0_26, PIO_UART_0},
	{P0_27, PIO_UART_0},
	{P0_28, PIO_UART_0},
	{P0_29, PIO_UART_0},
	{P0_30, PIO_I2C_2},
	{P0_31, PIO_I2C_2},
};

