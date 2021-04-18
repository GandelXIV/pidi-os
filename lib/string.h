#define STRCPY_OK 0

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

void strcpy(char* dest, char* src)
{
  uint size = strlen(src) + 1;
  for (uint i = 0; i < size; ++i)
  {
    dest[i] = src[i];
  }
}