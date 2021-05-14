#define INCLUDED_IO

#ifndef INCLUDED_DISPLAY
#include "../drivers/display.h"
#endif

#ifndef INCLUDED_KEYBOARD
#include "../drivers/keyboard.h"
#endif

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
  char input = 0;
  while (input != '\n')
  {
    input = kinputc();
    if (input == '\b' && i > 0)
    {
      --i;
      display_deletec();
    }
    else if (input != '\b')
    {
      kprintc(input);
      output[i] = input;
      ++i;
    }
  }
}
