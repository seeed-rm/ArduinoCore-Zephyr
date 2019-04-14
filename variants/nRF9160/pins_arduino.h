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

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

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


typedef enum _EPioType {
    PIO_GPIO,
    PIO_I2C0,
    PIO_I2C1,
    PIO_I2C2,
    PIO_SPI0,
    PIO_SPI1,
    PIO_SPI2,
    PIO_SPI3,
    PIO_UART0,
    PIO_UART1,
    PIO_PWM0,
    PIO_ADC,
    PIO_INVALID,
} EPioType;

const char * __attribute__((weak)) DevLab[] = {
	"GPIO_0",
	"I2C_0",
	"I2C_1",
	"I2C_2",
	"SPI_0",
	"SPI_1",
	"SPI_2",
	"SPI_3",
	"UART_0",
	"UART_1",
	"PWM0",
};

typedef const struct _PinDescription {
	uint32_t PinName;
	EPioType PioType;
} PinDescription;

#define PinMap_Max		(32)

PinDescription __attribute__((weak)) PinMap[PinMap_Max] = {
	{P0_00, PIO_UART0},
	{P0_01, PIO_UART0},
	{P0_02, PIO_GPIO},
	{P0_03, PIO_GPIO},
	{P0_04, PIO_GPIO},
	{P0_05, PIO_GPIO},
	{P0_06, PIO_GPIO},
	{P0_07, PIO_GPIO},
	{P0_08, PIO_GPIO},
	{P0_09, PIO_GPIO},
	{P0_10, PIO_UART0},
	{P0_11, PIO_UART0},
	{P0_12, PIO_GPIO},
	{P0_13, PIO_GPIO},
	{P0_14, PIO_GPIO},
	{P0_15, PIO_GPIO},
	{P0_16, PIO_GPIO},
	{P0_17, PIO_GPIO},
	{P0_18, PIO_GPIO},
	{P0_19, PIO_GPIO},
	{P0_20, PIO_UART0},
	{P0_21, PIO_UART0},
	{P0_22, PIO_GPIO},
	{P0_23, PIO_GPIO},
	{P0_24, PIO_GPIO},
	{P0_25, PIO_GPIO},
	{P0_26, PIO_GPIO},
	{P0_27, PIO_GPIO},
	{P0_28, PIO_GPIO},
	{P0_29, PIO_GPIO},
	{P0_30, PIO_UART0},
	{P0_31, PIO_UART0},
};


#endif // Pins_Arduino_h
