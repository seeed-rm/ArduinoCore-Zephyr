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

#ifndef Variant_h
#define Variant_h

#include <stdint.h>

#define PinMap_Max		(32)

#define NC          (0xffffffff)
#define P0_00		(0)
#define P0_01		(1)
#define P0_02		(2)
#define P0_03		(3)
#define P0_04		(4)
#define P0_05		(5)
#define P0_06		(6)
#define P0_07		(7)
#define P0_08		(8)
#define P0_09		(9)
#define P0_10		(10)
#define P0_11		(11)
#define P0_12		(12)
#define P0_13		(13)
#define P0_14		(14)
#define P0_15		(15)
#define P0_16		(16)
#define P0_17		(17)
#define P0_18		(18)
#define P0_19		(19)
#define P0_20		(20)
#define P0_21		(21)
#define P0_22		(22)
#define P0_23		(23)
#define P0_24		(24)
#define P0_25		(25)
#define P0_26		(26)
#define P0_27		(27)
#define P0_28		(28)
#define P0_29		(29)
#define P0_30		(30)
#define P0_31		(31)

#define DEV_GPIO_0_STRING	("GPIO_0")
#define DEV_SPI_0_STRING	("SPI_0")
#define DEV_SPI_1_STRING	("SPI_1")
#define DEV_SPI_2_STRING	("SPI_2")
#define DEV_SPI_3_STRING	("SPI_3")
#define DEV_I2C_0_STRING	("I2C_0")
#define DEV_I2C_1_STRING	("I2C_1")
#define DEV_I2C_2_STRING	("I2C_2")
#define DEV_I2C_3_STRING	("I2C_3")
#define DEV_UART_0_STRING	("UART_0")
#define DEV_UART_1_STRING	("UART_1")
#define DEV_UART_2_STRING	("UART_2")
#define DEV_UART_3_STRING	("UART_3")
#define DEV_I2S_STRING		("I2S")
#define DEV_PWM_0_STRING	("PWM_0")
#define DEV_PWM_1_STRING	("PWM_1")
#define DEV_PWM_2_STRING	("PWM_2")
#define DEV_ADC_0_STRING	("ADC_0")


typedef enum _EPioType {
    PIO_GPIO_0,
    PIO_SPI_0,
    PIO_SPI_1,
    PIO_SPI_2,
    PIO_SPI_3,
	PIO_I2C_0,
	PIO_I2C_1,
	PIO_I2C_2,
	PIO_I2C_3,
	PIO_UART_0,
    PIO_UART_1,
	PIO_UART_2,
	PIO_UART_3,
	PIO_I2S,
    PIO_PWM_0,
	PIO_PWM_1,
	PIO_PWM_2,
    PIO_ADC_0,
} EPioType;

typedef const struct _PinDescription {
	uint32_t PinName;
	EPioType PioType;
} PinDescription;


extern const char *DevLab[];
extern const PinDescription PinMap[PinMap_Max];

#endif // Variant_h