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

#ifndef INCLUDED_COLOR
#include "../drivers/display_color.h"
#endif

void kprinti(int number);
void kprintu(uint number);
void kprintu32(uint32_t number);
void kinputs(char* output);
