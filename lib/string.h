#define INCLUDED_STRING "cookie"
#ifndef INCLUDED_TYPE
#include "type.h"
#endif

// get string length
uint strlen(char* string)
{
  uint length = 0;
  while (*string != 0)
  {
    ++length;
    ++string;
  }
  return length;
}

// copy string
// NOTE: Does NOT check for string size -> string overflow!!!
void strcpy(char* dest, char* src)
{
  uint size = strlen(src) + 1;
  for (uint i = 0; i < size; ++i)
  {
    dest[i] = src[i];
  }
}

// compare 2 strings (checks if they are equal)
bool strcmp(char* a, char* b)
{
  uint32_t i = 0;
  while (1)
  {
    if (a[i] != b[i])
    {
      return false;
    }
    else if (a[i] == 0 && b[i] == 0)
    {
      return true;
    }
    ++i;
  }
}

// add the extenstion to the base string
// NOTE: Does NOT check for string size! -> string overflow!!!
void stradd(char* base, char* extension)
{
  strcpy(base + strlen(base), extension);
}

// fill string with zero
void strcls(char* string)
{
  while (*string != 0)
  {
    *string = 0;
    ++string;
  }
}

// convert char to upper case
char char_to_upper(char character)
{
  char offset = 'A' - 'a';
  if (character >= 'a' && character <= 'z')
  {
    return character + offset;
  }
  return character;
}

void strupp(char* string)
{
  while (*string != 0)
  {
    *string = char_to_upper(*string);
    ++string;
  }
}
