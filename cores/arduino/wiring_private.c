#include <zephyr.h>
#include <gpio.h>
#include "variant.h"

int gpio_configs[PinMap_Max] = {0};
struct gpio_callback gpio_cb[PinMap_Max];
