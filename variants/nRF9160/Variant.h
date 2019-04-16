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
#ifdef __cplusplus
#include "HardwareSerial.h"
#endif

#define ALL_GPIOS_NUM		(32)

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

#define DT_GPIO_0_LABEL	("GPIO_0")
#define DT_SPI_0_LABEL	("SPI_0")
#define DT_SPI_1_LABEL	("SPI_1")
#define DT_SPI_2_LABEL	("SPI_2")
#define DT_SPI_3_LABEL	("SPI_3")
#define DT_I2C_0_LABEL	("I2C_0")
#define DT_I2C_1_LABEL	("I2C_1")
#define DT_I2C_2_LABEL	("I2C_2")
#define DT_I2C_3_LABEL	("I2C_3")
#define DT_UART_0_LABEL	("UART_0")
#define DT_UART_1_LABEL	("UART_1")
#define DT_UART_2_LABEL	("UART_2")
#define DT_UART_3_LABEL	("UART_3")
#define DT_I2S_0_LABEL	("I2S_0")
#define DT_PWM_0_LABEL	("PWM_0")
#define DT_PWM_1_LABEL	("PWM_1")
#define DT_PWM_2_LABEL	("PWM_2")
#define DT_ADC_0_LABEL	("ADC_0")


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
extern const PinDescription PinMap[ALL_GPIOS_NUM];


#ifdef __cplusplus
extern HardwareSerial Serial;
extern HardwareSerial Serial1;

#endif

#endif // Variant_h