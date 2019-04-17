#include "UartACM.h"

void UartACM::begin(unsigned long baudrate, const char *label, uint32_t tx_pin, uint32_t rx_pin) {	
	#if 0
	u32_t dtr = 0;
	while (1) {
		uart_line_ctrl_get(uart, LINE_CTRL_DTR, &dtr);
		if (dtr)
			break;
	}

#if 0
	/* They are optional, we use them to test the interrupt endpoint */
	ret = uart_line_ctrl_set(uart, LINE_CTRL_DCD, 1);
	if (ret)
		printf("Failed to set DCD, ret code %d\n", ret);

	ret = uart_line_ctrl_set(uart, LINE_CTRL_DSR, 1);
	if (ret)
		printf("Failed to set DSR, ret code %d\n", ret);

	/* Wait 1 sec for the host to do all settings */
	k_busy_wait(1000000);

	ret = uart_line_ctrl_get(uart, LINE_CTRL_BAUD_RATE, &baudrate);
	if (ret)
		printf("Failed to get baudrate, ret code %d\n", ret);
	else
		printf("Baudrate detected: %d\n", baudrate);
#endif

	#endif
	begin(baudrate, SERIAL_8N1, label, tx_pin, rx_pin);
}

void UartACM::begin(unsigned long baudrate, uint16_t config, const char *label, uint32_t tx_pin, uint32_t rx_pin) {	
	#if 0
	u32_t dtr = 0;
	while (1) {
		uart_line_ctrl_get(uart, LINE_CTRL_DTR, &dtr);
		if (dtr)
			break;
	}

#if 0
	/* They are optional, we use them to test the interrupt endpoint */
	ret = uart_line_ctrl_set(uart, LINE_CTRL_DCD, 1);
	if (ret)
		printf("Failed to set DCD, ret code %d\n", ret);

	ret = uart_line_ctrl_set(uart, LINE_CTRL_DSR, 1);
	if (ret)
		printf("Failed to set DSR, ret code %d\n", ret);

	/* Wait 1 sec for the host to do all settings */
	k_busy_wait(1000000);

	ret = uart_line_ctrl_get(uart, LINE_CTRL_BAUD_RATE, &baudrate);
	if (ret)
		printf("Failed to get baudrate, ret code %d\n", ret);
	else
		printf("Baudrate detected: %d\n", baudrate);
#endif

	#endif
	HardwareSerial::begin(baudrate, config, label, tx_pin, rx_pin);
}

