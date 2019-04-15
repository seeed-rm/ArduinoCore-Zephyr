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

#define ARDUINO_MAIN
#include <zephyr.h>
#include <misc/printk.h>

#include "Arduino.h"

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

// Initialize C library
extern "C" void __libc_init_array(void);

/*
 * \brief Main entry point of Arduino application
 */

// test {
void setup(void) {
	pinMode(2, OUTPUT);
	analogWrite(2, 0);
}

int flag = 0;
/* in micro second */
#define MIN_PERIOD	10

/* in micro second */
#define MAX_PERIOD	4000

void loop(void) {
	#if 0
	digitalWrite(2, HIGH); // sets the digital pin 13 on
	delay(1000);            // waits for a second
	digitalWrite(2, LOW);  // sets the digital pin 13 off
	delay(1000);            // waits for a second
	printk("%s->digital LED\r\n", CONFIG_BOARD);
	#else
	if (flag) {
		flag = 0;
		analogWrite(2, MIN_PERIOD);
	} else {
		flag = 1;
		analogWrite(2, MAX_PERIOD);
	}
	delay(1000); 
	printk("%s->analog LED\r\n", CONFIG_BOARD);
	#endif
}
//} test

int main( void )
{
  init();
	printk("Hello World! %s\n", CONFIG_BOARD);
#if defined(CONFIG_NEWLIB_LIBC)
  __libc_init_array();
#endif

  initVariant();

  delay(1);
#if defined(USBCON)
  USBDevice.init();
  USBDevice.attach();
#endif

  setup();

  for (;;)
  {
    loop();
    if (serialEventRun) serialEventRun();
    k_yield();
  }

  return 0;
}

