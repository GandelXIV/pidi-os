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


void uint32_to_str(char* output, uint32_t number);
void uint_to_str(char* output, uint number);
void int_to_str(char* output, int number);
void short_to_str(char* output, short number);
char uint32_to_char(uint32_t number);
char uint_to_char(uint number);
byte char_to_hex(char character);
