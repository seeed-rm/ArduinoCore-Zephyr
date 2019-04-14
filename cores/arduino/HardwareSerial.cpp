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

#include <stdio.h>
#include "Arduino.h"
#include "HardwareSerial.h"

// Constructors ////////////////////////////////////////////////////////////////
HardwareSerial::HardwareSerial(uint32_t _rx, uint32_t _tx) {
	init();
}

void HardwareSerial::init(void) {
}

void HardwareSerial::begin(unsigned long baudrate) {
	begin(baudrate, SERIAL_8N1);
}

void HardwareSerial::begin(unsigned long baud, uint16_t conf) {
	begin_impl(baud, conf);
}

void HardwareSerial::begin_impl(unsigned long baud, uint16_t conf)
{
	//TODO newapi
	uart_irq_callback_user_data_set(uart, HardwareSerial::IrqDispatch, this);
	uart_irq_rx_enable(uart);
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
	reinterpret_cast<Uart*>(data)->IrqHandler();
}

int HardwareSerial::available(void) {
	return (uint32_t)(SERIAL_BUFFER_SIZE + rxBuffer._iHead - rxBuffer._iTail) % SERIAL_BUFFER_SIZE;
}

int HardwareSerial::availableForWrite(void) {
	return 0;//return uart->txbuffer_availables(uart->portinfo);
}

void HardwareSerial::flush() {
	//while (uart_irq_tx_complete(uart) );
}

int HardwareSerial::peek(void) {
	return rxBuffer.peek();
}

int HardwareSerial::read(void) {
	return rxBuffer.read_char();
}

size_t HardwareSerial::write(uint8_t *buffer, size_t size) {
	int written = 0;
	int length = size;
	
	uart_irq_tx_enable(uart);

	while (length) {
		data_transmitted = false;
		
		written = uart_fifo_fill(uart, buffer, length);
		while (data_transmitted == false) {
			k_yield();
		}

		length -= written;
		buffer += written;
	}

	uart_irq_tx_disable(uart);
	return 0;
}

size_t HardwareSerial::write(uint8_t c) {
	return write(&c, 1);
}

