#define INCLUDED_CONV
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
    uint32_t exp = (uint32_t) pow(10, (double) length - 1);
    if (number >= exp * 9){ output[write_index] = '9'; number -= exp * 9; }
    else if (number >= exp * 8){ output[write_index] = '8'; number -= exp * 8; }
    else if (number >= exp * 7) { output[write_index] = '7'; number -= exp * 7; }
    else if (number >= exp * 6) { output[write_index] = '6'; number -= exp * 6; }
    else if (number >= exp * 5) { output[write_index] = '5'; number -= exp * 5; }
    else if (number >= exp * 4) { output[write_index] = '4'; number -= exp * 4; }
    else if (number >= exp * 3) { output[write_index] = '3'; number -= exp * 3; }
    else if (number >= exp * 2) { output[write_index] = '2'; number -= exp * 2; }
    else if (number >= exp) { output[write_index] = '1'; number -= exp; }
    else { output[write_index] = '0'; }
    --length;
    ++write_index;
  }
}

void uint_to_str(char* output, uint number)
{
  uint32_to_str(output, (uint32_t) number);
}

void int_to_str(char* output, int number)
{
  if (number < 0)
  {
    output[0] = '-';  // set the first byte to '-', indicating its a negative
    ++output;         // we dont want to overwrite the '-'
    number = -number; // negate the negative number, making it positive
  }
  uint_to_str(output, number);
}

void short_to_str(char* output, short number)
{
  int_to_str(output, (int) number);
}

char uint32_to_char(uint32_t number)
{
  switch (number) {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
  }
}

char uint_to_char(uint number)
{
  return uint32_to_char((uint32_t) number);
}

byte char_to_hex(char character)
{
  switch (character)
  {
    case '0': return 0x0;
    case '1': return 0x1;
    case '2': return 0x2;
    case '3': return 0x3;
    case '4': return 0x4;
    case '5': return 0x5;
    case '6': return 0x6;
    case '7': return 0x7;
    case '8': return 0x8;
    case '9': return 0x9;
    case 'a': return 0xA;
    case 'A': return 0xA;
    case 'b': return 0xB;
    case 'B': return 0xB;
    case 'c': return 0xC;
    case 'C': return 0xC;
    case 'd': return 0xD;
    case 'D': return 0xD;
    case 'e': return 0xE;
    case 'E': return 0xE;
    case 'f': return 0xF;
    case 'F': return 0xF;
  }
}
