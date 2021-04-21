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

void uint32_to_str(char* output, uint32_t number)
{
  if (number == 0)
  {
      strcpy(output, "0"); // lol
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
    // xyz >= 10^d
    // too lazy to fix this mess
    if (number >= (uint32_t) pow(10, (double) length - 1) * 9){ output[write_index] = '9'; number -= (uint32_t) pow(10, (double) length - 1) * 9; }
    else if (number >= (uint32_t) pow(10, (double) length - 1) * 8){ output[write_index] = '8'; number -= (uint32_t) pow(10, (double) length - 1) * 8; }
    else if (number >= (uint32_t) pow(10, (double) length - 1) * 7) { output[write_index] = '7'; number -= (uint32_t) pow(10, (double) length - 1) * 7; }
    else if (number >= (uint32_t) pow(10, (double) length - 1) * 6) { output[write_index] = '6'; number -= (uint32_t) pow(10, (double) length - 1) * 6; }
    else if (number >= (uint32_t) pow(10, (double) length - 1) * 5) { output[write_index] = '5'; number -= (uint32_t) pow(10, (double) length - 1) * 5; }
    else if (number >= (uint32_t) pow(10, (double) length - 1) * 4) { output[write_index] = '4'; number -= (uint32_t) pow(10, (double) length - 1) * 4; }
    else if (number >= (uint32_t) pow(10, (double) length - 1) * 3) { output[write_index] = '3'; number -= (uint32_t) pow(10, (double) length - 1) * 3; }
    else if (number >= (uint32_t) pow(10, (double) length - 1) * 2) { output[write_index] = '2'; number -= (uint32_t) pow(10, (double) length - 1) * 2; }
    else if (number >= (uint32_t) pow(10, (double) length - 1)) { output[write_index] = '1'; number -= (uint32_t) pow(10, (double) length - 1); }
    else { output[write_index] = '0'; }
    --length;
    ++write_index;
  }
}

void uint_to_str(char* output, uint number)
{
  uint32_to_str(output, (uint32_t) number);
}

char uint32_to_char(uint32_t number)
{
  // no need for else if statements, because of the returns;
  if (number == 0) return '0';
  if (number == 1) return '1';
  if (number == 2) return '2';
  if (number == 3) return '3';
  if (number == 4) return '4';
  if (number == 5) return '5';
  if (number == 6) return '6';
  if (number == 7) return '7';
  if (number == 8) return '8';
  if (number == 9) return '9';
}
