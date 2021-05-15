#define INCLUDED_STRING
#ifndef INCLUDED_TYPE
#include "type.h"
#endif

uint strlen(char* string);
void strcpy(char* dest, char* src);
bool strcmp(char* a, char* b);
void stradd(char* base, char* extension);
void strcls(char* string);
char char_to_upper(char character);
void strupp(char* string);
