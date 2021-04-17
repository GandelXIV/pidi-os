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
