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

HardwareSerial::HardwareSerial() {
}

void HardwareSerial::uart_irq_cb() {
	int i = 0;
	int length = 0;
	uint8_t uart_buf[32] = {0};
	int w_length = 0;
	
	uart_irq_update(uart);

	if (uart_irq_rx_ready(uart)) {
		length = uart_fifo_read(uart, uart_buf, sizeof(uart_buf));
		for (i = 0; i < length; i++) {
			_rx_buffer->store_char(uart_buf[i]);
		}
	}

	if (uart_irq_tx_ready(uart)) {
		if (_tx_buffer->_iHead != _tx_buffer->_iTail) {
			length = uart_fifo_fill(uart, &(_tx_buffer->_aucBuffer[_tx_buffer->_iTail]), 1);
			if (1 == length) {
				w_length = (_tx_buffer->_iTail + 1) % SERIAL_BUFFER_SIZE;
				_tx_buffer->_iTail = w_length;
			}
		}
	}
	
	if (uart_irq_tx_complete(uart)) {
		uart_irq_tx_disable(uart);
	}
}

void HardwareSerial::uart_irq_dispatch(void *userdata) {
	reinterpret_cast<HardwareSerial *>(userdata)->uart_irq_cb();
}

void HardwareSerial::init() {
	_tx_buffer = new RingBuffer();
	_rx_buffer = new RingBuffer();

	_tx_buffer->_iHead = _tx_buffer->_iTail = 0;
	_rx_buffer->_iHead = _rx_buffer->_iTail = 0;
}

void HardwareSerial::begin(unsigned long baudrate, const char *label, uint32_t tx_pin, uint32_t rx_pin) {
	begin(baudrate, SERIAL_8N1, label, tx_pin, rx_pin);
}

void HardwareSerial::begin(unsigned long baudrate, uint16_t config, const char *label, uint32_t tx_pin, uint32_t rx_pin) {
	struct uart_config uart_cfg;

	uart_cfg.baudrate = baudrate;
	uart_cfg.parity = config & 0x0f;
	uart_cfg.stop_bits = (config >> 4) & 0x0f;
	uart_cfg.data_bits = (config >> 8) & 0x0f;
	uart_cfg.flow_ctrl = (config >> 12) & 0x0f;

	uart = device_get_binding(label);
	
	if (NULL != uart) {
		printk("set callback function\r\n");
		uart_configure(uart, &uart_cfg);
		uart_irq_callback_user_data_set(uart, uart_irq_dispatch, this);
		uart_irq_rx_enable(uart);
		
		init();
	}
}

void HardwareSerial::end() {	
	// Clear any received data
	_rx_buffer->_iHead = _rx_buffer->_iTail;
	
	// Wait for any outstanding data to be sent
	flush();
}

int HardwareSerial::available() {
	return (uint32_t)(SERIAL_BUFFER_SIZE + _rx_buffer->_iHead - _rx_buffer->_iTail) % SERIAL_BUFFER_SIZE;
}

int HardwareSerial::availableForWrite() {
	int tx_head = _tx_buffer->_iHead;
	int tx_tail = _tx_buffer->_iTail;
	
	if (tx_head >= tx_tail) {
		return SERIAL_BUFFER_SIZE - 1 - tx_head + tx_tail;
	}
	return tx_tail - tx_head - 1;	
}

int HardwareSerial::peek() {
	if (_rx_buffer->_iHead == _rx_buffer->_iTail) {
		return -1;
	}
	
	return _rx_buffer->_aucBuffer[_rx_buffer->_iTail];
}

int HardwareSerial::read() {
	uint8_t data = 0;

	// if the head isn't ahead of the tail, we don't have any characters
	if (_rx_buffer->_iHead == _rx_buffer->_iTail) {
		return -1;
	}
	
	data = _rx_buffer->_aucBuffer[_rx_buffer->_iTail];
	_rx_buffer->_iTail = (unsigned int)(_rx_buffer->_iTail + 1) % SERIAL_BUFFER_SIZE;
	return data;
}

void HardwareSerial::flush(void) {
	//wait for transmit data to be sent
	while (_tx_buffer->_iHead != _tx_buffer->_iTail);
	
	// Wait for transmission to complete
	while (uart_irq_tx_complete(uart));
}

size_t HardwareSerial::write(const uint8_t data) {
	int nextWrite;

	// If busy we buffer
	nextWrite = (_tx_buffer->_iHead + 1) % SERIAL_BUFFER_SIZE;
	// Spin locks if we're about to overwrite the buffer. This continues once the data is sent
	while (_tx_buffer->_iTail == nextWrite);
	
	_tx_buffer->_aucBuffer[_tx_buffer->_iHead] = data;
	_tx_buffer->_iHead = nextWrite;
	uart_irq_tx_enable(uart);
	return 0;
}
