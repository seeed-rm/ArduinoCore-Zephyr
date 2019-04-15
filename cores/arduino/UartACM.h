#include <zephyr.h>
#include <device.h>
#include <gpio.h>
#include <uart.h>

#include "HardwareSerial.h"

class UartACM : public HardwareSerial
{
  public:
    UartACM(uint32_t _rx, uint32_t _tx);// : HardwareSerial(uint32_t _rx, uint32_t _tx) { }
  protected:
    void begin_impl(unsigned long baudrate, uint16_t config);
};
