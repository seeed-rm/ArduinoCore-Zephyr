/*
  Copyright (c) 2015-2016 Tokita, Hiroshi  All right reserved.

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

#include <zephyr.h>
#include <device.h>
#include <gpio.h>
#include <uart.h>

#include "variant.h"
#include "HardwareSerial.h"

#ifdef __cplusplus
extern "C" {
#include "PeripheralPins.h"
}
#endif

#ifndef max
#define max(A, B) ((A) < (B) ? (B) : (A))
#endif

HardwareSerial::HardwareSerial() {
	uart = device_get_binding("UART_0");
}

void HardwareSerial::begin(unsigned long baudrate, uint32_t tx_pin, uint32_t rx_pin) {
	begin(baudrate, SERIAL_8N1, tx_pin, rx_pin);
}

void HardwareSerial::begin(unsigned long baudrate, uint16_t config, uint32_t tx_pin, uint32_t rx_pin) {
	uint8_t index = 0xff;
	struct uart_config uart_cfg;

	uart_cfg.baudrate = baudrate;
	uart_cfg.parity = config & 0x0f;
	uart_cfg.stop_bits = (config >> 4) & 0x0f;
	uart_cfg.data_bits = (config >> 8) & 0x0f;
	uart_cfg.flow_ctrl = (config >> 12) & 0x0f;

	if ((tx_pin != rx_pin) || (tx_pin < ALL_GPIOS_NUM) || (rx_pin < ALL_GPIOS_NUM)) {
		if (0xff != (index = pin_in_PeripheralPinMap(PinMap[tx_pin].PinName, PinMap_UART_TX))) {
			uart = device_get_binding(PinMap_UART_TX[index].label_name);
			printk("tx->label = %s\r\n", PinMap_UART_TX[index].label_name);
		} else if (0xff != (index = pin_in_PeripheralPinMap(PinMap[rx_pin].PinName, PinMap_UART_RX))) {
			uart = device_get_binding(PinMap_UART_RX[index].label_name);
			printk("rx->label = %s\r\n", PinMap_UART_RX[index].label_name);
		} else {
			uart = NULL;
			printk("label is NULL\r\n");
		}
		
		if (NULL != uart) {
			printk("set callback function\r\n");
			uart_configure(uart, &uart_cfg);
			uart_irq_callback_user_data_set(uart, IrqDispatch, this);
			uart_irq_rx_enable(uart);
		}
	}
}

void HardwareSerial::end()
{
	flush();
	//uart->deinit(uart->portinfo);
}

void HardwareSerial::flush()
{
	//while (uart_irq_tx_complete(uart) );
}

void HardwareSerial::IrqHandler()
{
	uart_irq_update(uart);

	if (uart_irq_tx_ready(uart)) {
		data_transmitted = true;
	}

	int rxcount = uart_irq_rx_ready(uart);
	if(rxcount == 0) return;

	do {
		static uint8_t buf[32];
		int ret = uart_fifo_read(uart, buf, max(rxcount, 32) ); 
		if(ret) {
			for(int i=0; i<max(rxcount, 32); i++) {
				rxBuffer.store_char(buf[i]);
			}
		}
		rxcount = uart_irq_rx_ready(uart);
	} while(rxcount > 0);
}

void HardwareSerial::IrqDispatch(void* data)
{
	reinterpret_cast<HardwareSerial *>(data)->IrqHandler();
}

int HardwareSerial::available()
{
	return (uint32_t)(SERIAL_BUFFER_SIZE + rxBuffer._iHead - rxBuffer._iTail) % SERIAL_BUFFER_SIZE;
}

int HardwareSerial::availableForWrite()
{
	return 0;//return uart->txbuffer_availables(uart->portinfo);
}

int HardwareSerial::peek()
{
	return rxBuffer.peek();
}

int HardwareSerial::read()
{
	return rxBuffer.read_char();
}

size_t HardwareSerial::write(const uint8_t *buffer, size_t size)
{
	uart_irq_tx_enable(uart);

	int len = size;
	while (len) {
		int written;

		data_transmitted = false;
		written = uart_fifo_fill(uart, buffer, len);
		while (data_transmitted == false) {
			k_yield();
		}

		len -= written;
		buffer += written;
	}

	uart_irq_tx_disable(uart);
	return 0;
}


size_t HardwareSerial::write(const uint8_t data)
{
	write(&data, 1);
	return 1;
}
