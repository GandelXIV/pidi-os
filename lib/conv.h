#define INCLUDED_CONV "cookie"
#ifndef INCLUDED_TYPE
#include "type.h"
#endif
#ifndef INCLUDED_MATH
#include "math.h"
#endif
#ifndef INCLUDED_STRING
#include "string.h"
#endif

void uint32_to_str(char* target, uint32_t number)
{
  if (number == 0)
  {
      strcpy(target, "0"); // lol
      return;
  }
  // get digit count
  uint32_t length = 0;
  while ( number > pow(10, (double) length) )
  {
    ++length;
  }
  uint32_t write_index = 0;
  while ( length > 0 )
  {
    if (number >= (uint32_t) pow(10, (double) length - 1) * 9)
    {
      target[write_index] = '9';
      number -= (uint32_t) pow(10, (double) length - 1) * 9;
    }
    else if (number >= (uint32_t) pow(10, (double) length - 1) * 8)
    {
      target[write_index] = '8';
      number -= (uint32_t) pow(10, (double) length - 1) * 8;
    }
    else if (number >= (uint32_t) pow(10, (double) length - 1) * 7)
    {
      target[write_index] = '7';
      number -= (uint32_t) pow(10, (double) length - 1) * 7;
    }
    else if (number >= (uint32_t) pow(10, (double) length - 1) * 6)
    {
      target[write_index] = '6';
      number -= (uint32_t) pow(10, (double) length - 1) * 6;
    }
    else if (number >= (uint32_t) pow(10, (double) length - 1) * 5)
    {
      target[write_index] = '5';
      number -= (uint32_t) pow(10, (double) length - 1) * 5;
    }
    else if (number >= (uint32_t) pow(10, (double) length - 1) * 4)
    {
      target[write_index] = '4';
      number -= (uint32_t) pow(10, (double) length - 1) * 4;
    }
    else if (number >= (uint32_t) pow(10, (double) length - 1) * 3)
    {
      target[write_index] = '3';
      number -= (uint32_t) pow(10, (double) length - 1) * 3;
    }
    else if (number >= (uint32_t) pow(10, (double) length - 1) * 2)
    {
      target[write_index] = '2';
      number -= (uint32_t) pow(10, (double) length - 1) * 2;
    }
    else if (number >= (uint32_t) pow(10, (double) length - 1))
    {
      target[write_index] = '1';
      number -= (uint32_t) pow(10, (double) length - 1);
    }
    else
    {
      target[write_index] = '0';
    }
    --length;
    ++write_index;
  }
}
