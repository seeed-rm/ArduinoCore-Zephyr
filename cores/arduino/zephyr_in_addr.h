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

#include <stdint.h>

#ifndef ZEPHYR_IN_ADDR__
#define ZEPHYR_IN_ADDR__

struct z_v4data {
  union {
    uint8_t bytes[4];
    uint32_t dword;
  };
};

struct z_v4map_addr {
#if defined(CONFIG_NET_IPV6)
  uint8_t prefix[12];
#else
  uint8_t prefix[0];
#endif
  struct z_v4data v4;
};

struct z_in_addr {
  union {
#if defined(CONFIG_NET_IPV6)
    uint16_t u16[8];
    uint8_t u8[16];
#else
    uint16_t u16[2];
    uint8_t u8[4];
#endif
    struct z_v4map_addr v4map;
  };
};

#endif //ZEPHYR_IN_ADDR__

