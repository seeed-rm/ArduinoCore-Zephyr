#include <zephyr.h>
#include <gpio.h>
#include "wiring_private.h"

int gpio_configs[ALL_GPIOS_NUM] = {0};
struct gpio_callback gpio_cb[ALL_GPIOS_NUM];


