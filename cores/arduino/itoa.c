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

#include "itoa.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* reverse:  reverse string s in place */
/*
static void reverse( char s[] )
{
  int i, j ;
  char c ;

  for ( i = 0, j = strlen(s)-1 ; i < j ; i++, j-- )
  {
    c = s[i] ;
    s[i] = s[j] ;
    s[j] = c ;
  }
}
*/

/* itoa:  convert n to characters in s */
/*
extern void itoa( int n, char s[] )
{
  int i, sign ;

  if ( (sign = n) < 0 )  // record sign
  {
    n = -n;          // make n positive
  }

  i = 0;
  do
  {       // generate digits in reverse order
    s[i++] = n % 10 + '0';   // get next digit
  } while ((n /= 10) > 0) ;     // delete it

  if (sign < 0 )
  {
    s[i++] = '-';
  }

  s[i] = '\0';

  reverse( s ) ;
}
*/

extern char* itoa( int value, char *string, int radix )
{
  return ltoa( value, string, radix ) ;
}

extern char* ltoa( long value, char *string, int radix )
{
  char tmp[33];
  char *tp = tmp;
  long i;
  unsigned long v;
  int sign;
  char *sp;

  if ( string == NULL )
  {
    return 0 ;
  }

  if (radix > 36 || radix <= 1)
  {
    return 0 ;
  }

  sign = (radix == 10 && value < 0);
  if (sign)
  {
    v = -value;
  }
  else
  {
    v = (unsigned long)value;
  }

  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  sp = string;

  if (sign)
    *sp++ = '-';
  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;

  return string;
}

extern char* utoa( unsigned int value, char *string, int radix )
{
  return ultoa( value, string, radix ) ;
}

extern char* ultoa( unsigned long value, char *string, int radix )
{
  char tmp[33];
  char *tp = tmp;
  long i;
  unsigned long v = value;
  char *sp;

  if ( string == NULL )
  {
    return 0;
  }

  if (radix > 36 || radix <= 1)
  {
    return 0;
  }

  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  sp = string;


  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;

  return string;
}

#ifdef __cplusplus
} // extern "C"
#endif
