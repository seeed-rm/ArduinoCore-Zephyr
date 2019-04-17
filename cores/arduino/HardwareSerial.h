/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

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
#pragma once

#ifndef HardwareSerial_h
#define HardwareSerial_h
#ifdef __cplusplus
#include <inttypes.h>

#include "Stream.h"
#include "RingBuffer.h"

#define SERIAL_PARITY_NONE 		(0x0ul)
#define SERIAL_PARITY_ODD		(0x1ul)
#define SERIAL_PARITY_EVEN 		(0x2ul)
#define SERIAL_PARITY_MARK		(0x3ul)
#define SERIAL_PARITY_SPACE		(0x4ul)

#define SERIAL_STOP_BIT_0_5		(0x00ul)
#define SERIAL_STOP_BIT_1		(0x10ul)
#define SERIAL_STOP_BIT_1_5		(0x20ul)
#define SERIAL_STOP_BIT_2	 	(0x30ul)
#define SERIAL_STOP_BIT_MASK	(0xF0ul)

#define SERIAL_DATA_5	 		(0x000ul)
#define SERIAL_DATA_6	 		(0x100ul)
#define SERIAL_DATA_7	 		(0x200ul)
#define SERIAL_DATA_8	 		(0x300ul)
#define SERIAL_DATA_MASK		(0xF00ul)

#define SERIAL_FLOW_CTRL_NONE		(0x0000ul)
#define SERIAL_FLOW_CTRL_RTS_CTS	(0x1000ul)
#define SERIAL_FLOW_CTRL_DTR_DSR	(0x2000ul)




#define SERIAL_5N1				(SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE | SERIAL_DATA_5)
#define SERIAL_6N1				(SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE | SERIAL_DATA_6)
#define SERIAL_7N1				(SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE | SERIAL_DATA_7)
#define SERIAL_8N1				(SERIAL_STOP_BIT_1 | SERIAL_PARITY_NONE | SERIAL_DATA_8)
#define SERIAL_5N2				(SERIAL_STOP_BIT_2 | SERIAL_PARITY_NONE | SERIAL_DATA_5)
#define SERIAL_6N2				(SERIAL_STOP_BIT_2 | SERIAL_PARITY_NONE | SERIAL_DATA_6)
#define SERIAL_7N2				(SERIAL_STOP_BIT_2 | SERIAL_PARITY_NONE | SERIAL_DATA_7)
#define SERIAL_8N2				(SERIAL_STOP_BIT_2 | SERIAL_PARITY_NONE | SERIAL_DATA_8)
#define SERIAL_5E1				(SERIAL_STOP_BIT_1 | SERIAL_PARITY_EVEN | SERIAL_DATA_5)
#define SERIAL_6E1				(SERIAL_STOP_BIT_1 | SERIAL_PARITY_EVEN | SERIAL_DATA_6)
#define SERIAL_7E1				(SERIAL_STOP_BIT_1 | SERIAL_PARITY_EVEN | SERIAL_DATA_7)
#define SERIAL_8E1				(SERIAL_STOP_BIT_1 | SERIAL_PARITY_EVEN | SERIAL_DATA_8)
#define SERIAL_5E2				(SERIAL_STOP_BIT_2 | SERIAL_PARITY_EVEN | SERIAL_DATA_5)
#define SERIAL_6E2				(SERIAL_STOP_BIT_2 | SERIAL_PARITY_EVEN | SERIAL_DATA_6)
#define SERIAL_7E2				(SERIAL_STOP_BIT_2 | SERIAL_PARITY_EVEN | SERIAL_DATA_7)
#define SERIAL_8E2				(SERIAL_STOP_BIT_2 | SERIAL_PARITY_EVEN | SERIAL_DATA_8)
#define SERIAL_5O1				(SERIAL_STOP_BIT_1 | SERIAL_PARITY_ODD  | SERIAL_DATA_5)
#define SERIAL_6O1				(SERIAL_STOP_BIT_1 | SERIAL_PARITY_ODD  | SERIAL_DATA_6)
#define SERIAL_7O1				(SERIAL_STOP_BIT_1 | SERIAL_PARITY_ODD  | SERIAL_DATA_7)
#define SERIAL_8O1				(SERIAL_STOP_BIT_1 | SERIAL_PARITY_ODD  | SERIAL_DATA_8)
#define SERIAL_5O2				(SERIAL_STOP_BIT_2 | SERIAL_PARITY_ODD  | SERIAL_DATA_5)
#define SERIAL_6O2				(SERIAL_STOP_BIT_2 | SERIAL_PARITY_ODD  | SERIAL_DATA_6)
#define SERIAL_7O2				(SERIAL_STOP_BIT_2 | SERIAL_PARITY_ODD  | SERIAL_DATA_7)
#define SERIAL_8O2				(SERIAL_STOP_BIT_2 | SERIAL_PARITY_ODD  | SERIAL_DATA_8)

class HardwareSerial : public Stream
{
	public:
		HardwareSerial();
		virtual ~HardwareSerial() {}
		void begin(unsigned long baudrate, const char *label, RingBuffer *pRx_buffer, RingBuffer *pTx_buffer, uint32_t tx_pin = 29, uint32_t rx_pin = 28);
		void begin(unsigned long baudrate, uint16_t config, const char *label, RingBuffer *pRx_buffer, RingBuffer *pTx_buffer, uint32_t tx_pin = 29, uint32_t rx_pin = 28);
		void end();
		int available();
		int availableForWrite();
		int peek();
		int read();
		void flush();
		size_t write(const uint8_t data);
		using Print::write; // pull in write(str) and write(buf, size) from Print
		void uart_irq_cb();
		operator bool() { return true; }
		void operator delete(void *ptr) {}

	protected:
		struct device *uart;

	private:
		RingBuffer *_rx_buffer;
	    RingBuffer *_tx_buffer;
		void init(RingBuffer *pRx_buffer, RingBuffer *pTx_buffer);
		static void uart_irq_dispatch(void *userdata);
		volatile bool data_transmitted;
};

extern void serialEventRun(void) __attribute__((weak));
#endif
#endif
