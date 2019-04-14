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

#ifdef __cplusplus

#ifndef _RING_BUFFER_
#define _RING_BUFFER_

#include <stdint.h>

// Define constants and variables for buffering incoming serial data.  We're
// using a ring buffer (I think), in which head is the index of the location
// to which to write the next incoming character and tail is the index of the
// location from which to read.
#define SERIAL_BUFFER_SIZE 64

template <int N>
class RingBufferN
{
  public:
    uint8_t _aucBuffer[N] ;
    volatile int _iHead ;
    volatile int _iTail ;

  public:
    RingBufferN( void ) ;
    void store_char( uint8_t c ) ;
    void clear();
    int read_char();
    int available();
    int availableForStore();
    int peek();
    bool isFull();

  private:
    int nextIndex(int index);
};

typedef RingBufferN<SERIAL_BUFFER_SIZE> RingBuffer;


template <int N>
RingBufferN<N>::RingBufferN( void )
{
    memset( _aucBuffer, 0, N ) ;
    clear();
}

template <int N>
void RingBufferN<N>::store_char( uint8_t c )
{
  int i = nextIndex(_iHead);

  // if we should be storing the received character into the location
  // just before the tail (meaning that the head would advance to the
  // current location of the tail), we're about to overflow the buffer
  // and so we don't write the character or advance the head.
  if ( i != _iTail )
  {
    _aucBuffer[_iHead] = c ;
    _iHead = i ;
  }
}

template <int N>
void RingBufferN<N>::clear()
{
  _iHead = 0;
  _iTail = 0;
}

template <int N>
int RingBufferN<N>::read_char()
{
  if(_iTail == _iHead)
    return -1;

  uint8_t value = _aucBuffer[_iTail];
  _iTail = nextIndex(_iTail);

  return value;
}

template <int N>
int RingBufferN<N>::available()
{
  int delta = _iHead - _iTail;

  if(delta < 0)
    return N + delta;
  else
    return delta;
}

template <int N>
int RingBufferN<N>::availableForStore()
{
  if (_iHead >= _iTail)
    return N - 1 - _iHead + _iTail;
  else
    return _iTail - _iHead - 1;
}

template <int N>
int RingBufferN<N>::peek()
{
  if(_iTail == _iHead)
    return -1;

  return _aucBuffer[_iTail];
}

template <int N>
int RingBufferN<N>::nextIndex(int index)
{
  return (uint32_t)(index + 1) % N;
}

template <int N>
bool RingBufferN<N>::isFull()
{
  return (nextIndex(_iHead) == _iTail);
}

#endif /* _RING_BUFFER_ */

#endif /* __cplusplus */
