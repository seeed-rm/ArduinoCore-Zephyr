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

#ifndef client_h
#define client_h
#include "Print.h"
#include "Stream.h"
#include "IPAddress.h"

class Client : public Stream {
	public:
		virtual int connect(IPAddress ip, uint16_t port) =0;
		virtual int connect(const char *host, uint16_t port) =0;
		virtual size_t write(uint8_t) =0;
		virtual size_t write(const uint8_t *buf, size_t size) =0;
		virtual int available() = 0;
		virtual int read() = 0;
		virtual int read(uint8_t *buf, size_t size) = 0;
		virtual int peek() = 0;
		virtual void flush() = 0;
		virtual void stop() = 0;
		virtual uint8_t connected() = 0;
		virtual operator bool() = 0;
	protected:
		uint8_t* rawIPAddress(IPAddress& addr) { return addr.raw_address(); };
};
 
#endif // client_h
