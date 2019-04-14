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

#ifndef IPAddress_h
#define IPAddress_h

#include <stdint.h>
#include <zephyr/types.h>
#include <misc/byteorder.h>

#include "Printable.h"
#include "WString.h"
#include "zephyr_in_addr.h"

// A class to make it easier to handle and pass around IP addresses

class IPAddress : public Printable {
private:
    struct z_in_addr _address;

    // Access the raw byte array containing the address.  Because this returns a pointer
    // to the internal structure rather than a copy of the address this function should only
    // be used when you know that the usage of the returned uint8_t* will be transient and not
    // stored.
    uint8_t* raw_address() { return _address.v4map.v4.bytes; };
    uint16_t* raw_address6() { return _address.u16; };
    struct z_in_addr* raw_in_addr() { return &_address; };
    bool isV6MappedAddress() const;

public:
    // Constructors
    IPAddress();
    IPAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet);
    IPAddress(uint32_t address);
    IPAddress(const uint8_t *address);
#if defined(CONFIG_NET_IPV6)
    IPAddress(uint16_t d1, uint16_t d2, uint16_t d3, uint16_t d4,
              uint16_t d5, uint16_t d6, uint16_t d7, uint16_t d8);
    IPAddress(const uint16_t *address);
#endif

    bool fromString(const char *address);
    bool fromString(const String &address) { return fromString(address.c_str()); }

    // Overloaded cast operator to allow IPAddress objects to be used where a pointer
    // to a four-byte uint8_t array is expected
    operator uint32_t() const { return _address.v4map.v4.dword; };
#if defined(CONFIG_NET_IPV6)
    bool operator==(const IPAddress& addr) const { return ((*this) == addr._address.u16); };
#else
    bool operator==(const IPAddress& addr) const { return ((*this) == addr._address.u8); };
#endif
    bool operator==(const uint8_t* addr) const;
#if defined(CONFIG_NET_IPV6)
    bool operator==(const uint16_t* addr) const;
#endif

    // Overloaded index operator to allow getting and setting individual octets of the address
    uint8_t operator[](int index) const { return _address.v4map.v4.bytes[index]; };
    uint8_t& operator[](int index) { return _address.v4map.v4.bytes[index]; };

    // Overloaded copy operators to allow initialisation of IPAddress objects from other types
    IPAddress& operator=(const uint8_t *address);
    IPAddress& operator=(uint32_t address);
#if defined(CONFIG_NET_IPV6)
    IPAddress& operator=(const IPAddress& addr);
    IPAddress& operator=(const uint16_t *address);
#endif

    virtual size_t printTo(Print& p) const;

    friend class EthernetClass;
    friend class UDP;
    friend class Client;
    friend class Server;
    friend class DhcpClass;
    friend class DNSClient;

    class V6RawAccessor : public Printable
    {
        uint16_t* addr;
        V6RawAccessor(uint16_t* a) : addr(a) { }
        uint16_t* raw_address() { return addr; }

        public:
        uint16_t operator[](int index) const { return sys_be16_to_cpu(addr[index]); }
        //uint16_t& operator[](int index) { return sys_be16_to_cpu(addr[index]); }
        virtual size_t printTo(Print& p) const;

        friend class IPAddress;
    };

#if !defined(CONFIG_NET_IPV6)
private:
#endif
    V6RawAccessor v6;
};

const IPAddress INADDR_NONE(0,0,0,0);
#if defined(CONFIG_NET_IPV6)
const IPAddress IN6ADDR_ANY_INIT(0, 0, 0, 0, 0, 0, 0, 0);
const IPAddress IN6ADDR_LOOPBACK_INIT(0, 0, 0, 0, 0, 0, 0, 1);
const IPAddress IN6ADDR_LINKLOCAL_ALLNODES_INIT(  0xff02,0,0,0, 0,0,0,1);
const IPAddress IN6ADDR_LINKLOCAL_ALLROUTERS_INIT(0xff02,0,0,0, 0,0,0,2);
const IPAddress IN6ADDR_INTERFACELOCAL_ALLNODES_INIT(0xff01,0,0,0, 0,0,0,1);
const IPAddress IN6ADDR_INTERFACELOCAL_ALLROUTERS_INIT(0xff01,0,0,0, 0,0,0,2);
const IPAddress IN6ADDR_SITELOCAL_ALLROUTERS_INIT(0xff05,0,0,0, 0,0,0,2);
#endif

#endif
