#include <zephyr.h>
#include <device.h>
#include <gpio.h>
#include <uart.h>

#include "HardwareSerial.h"

class UartACM : public HardwareSerial {
	public:
		UartACM();
		void begin(unsigned long baudrate, const char *label, uint32_t tx_pin = 29, uint32_t rx_pin = 28);
		void begin(unsigned long baudrate, uint16_t config, const char *label, uint32_t tx_pin = 29, uint32_t rx_pin = 28);
};
