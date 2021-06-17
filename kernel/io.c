#include "io.h"

#include "../lib/conv.h"

// print string to cursor with color
void kprints_color(char* text, char color)
{
	while (*text != 0)
	{
		kprintc_color(*text, color);
		++text;
	}
}

// print string to cursor with default color
void kprints(char* text)
{
  kprints_color(text, TRANSPARENT);
}

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
  uint32_to_hex(output, number);
  kprints(output);
}

void kprinthex(uint32_t number)
{
  char* output;
  uint32_to_hex(output, number);
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
    else if (input == '\n') { output[i] = 0; }
    else if (input != '\b')
    {
      kprintc(input);
      output[i] = input;
      ++i;
    }
  }
  kprintc('\n');
}
