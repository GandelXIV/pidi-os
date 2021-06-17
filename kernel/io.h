#pragma once

#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "../drivers/display_color.h"


void kprinti(int number);
void kprintu(uint number);
void kprintu32(uint32_t number);
void kinputs(char* output);
void kprints(char* text);
void kprints_color(char* text, char color);
