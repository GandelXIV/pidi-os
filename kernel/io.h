#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#ifndef INCLUDED_CONV
#include "../lib/conv.h"
#endif

void kprinti(int number)
{
  char output [12];
  int_to_str(output, number);
  kprints(output);
}

void kprintu(uint number)
{
  char output [12];
  uint_to_str(output, number);
  kprints(output);
}

void kprintu32(uint32_t number)
{
  char output [12];
  uint32_to_str(output, number);
  kprints(output);
}

void kinputs(char* output)
{
  uint32_t i = 0;
  char input = kinputc();
  kprintc(input);
  while (input != '\n')
  {
    output[i] = input;
    ++i;
    input = kinputc();
    kprintc(input);
  }
}
