#include "../lib/type.h"
#define MEMORY_INIT uint32_t** memory = (uint32_t**) KERNEL_MEMORY_OFFSET;

void* kmalloc(uint size)
{
  MEMORY_INIT
  *memory += size;
  return *memory - size;
}

void kminit()
{
  MEMORY_INIT
  *memory = (uint32_t*) KERNEL_MEMORY_OFFSET + 20;  // to make sure
}

void memcpy(bytes dest, bytes src, uint32_t size)
{
  for (uint32_t i = 0; i < size; ++i)
  {
    dest[i] = src[i];
    ++i;
  }
}
