#define INCLUDED_MEM "cookie"
#ifndef INCLUDED_TYPE
#include "../lib/type.h"
#endif

#define MEMORY_INIT uint32_t** memory = (uint32_t**) KERNEL_MEMORY_OFFSET;

// NOTE: Can NOT be freed, so dont use it in loops
void* kmalloc(uint size)
{
  MEMORY_INIT
  *memory += size;
  return *memory - size;
}

// initializes kernel memory pointer -> allows for kmalloc() calls
void kminit()
{
  MEMORY_INIT
  *memory = (uint32_t*) KERNEL_MEMORY_OFFSET + 20;  // to make sure
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
