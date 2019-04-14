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

#include <zephyr.h>
#include <net/net_ip.h>

bool parse_ipaddr(const char* addr, uint8_t* buf)
{
    struct sockaddr sa;
    bool ret = net_ipaddr_parse(addr, strlen(addr), &sa);
    if(ret) {
        if(sa.sa_family == AF_INET6) {
#if defined(CONFIG_NET_IPV6)
            memcpy(buf, ((struct sockaddr_in6*)(&sa))->sin6_addr.s6_addr, 16);
#else
	    return false;
#endif
	}
	else if(sa.sa_family == AF_INET) {
#if defined(CONFIG_NET_IPV6)
            uint8_t prefix[12] = { 0,0,0,0,  0,0,0,0, 0,0,0xFF,0xFF};
            memcpy(buf, prefix, 12);
#endif
            memcpy(buf+12, ((struct sockaddr_in*)(&sa))->sin_addr.s4_addr, 4);
	}
    }
    return ret;
}

