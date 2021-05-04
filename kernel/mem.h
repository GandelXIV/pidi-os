#define INCLUDED_MEM "cookie"
#ifndef INCLUDED_TYPE
#include "../lib/type.h"
#endif

static byte* memp;  // pointer to free memory

// NOTE: Can NOT be freed, so dont use it in loops
void* kmalloc(uint size)
{
  *memp += size;
  return *memp - size;
}

// initializes kernel memory pointer -> allows for kmalloc() calls
void memory_init()
{
  memp = (byte*) KERNEL_MEMORY_OFFSET;
}

// copy memory
void memcpy(bytes dest, bytes src, uint32_t size)
{
  for (uint32_t i = 0; i < size; ++i)
  {
    dest[i] = src[i];
    ++i;
  }
}
