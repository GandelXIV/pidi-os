#include "type.h"

// get string length
uint strlen(char* string)
{
  uint length;
  while (*string != 0)
  {
    ++length;
    ++string;
  }
  return length;
}

// copy string
// NOTE: Does NOT check for string size -> does not prevent string overflow!!!
void strcpy(char* dest, char* src)
{
  uint size = strlen(src) + 1;
  for (uint i = 0; i < size; ++i)
  {
    dest[i] = src[i];
  }
}

// compares 2 strings (checks if they are equal)
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
