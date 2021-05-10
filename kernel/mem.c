#include "mem.h"

// index structure:
// even index -> page start
// odd index -> page end
byte* memory_index [1000];

// allocate memory
void* kmalloc(uint32_t size)
{
  uint i = 0;
  while (true)
  {
    // search
    while (memory_index[i] != MEMORY_EMPTY) { i += 2; }
    byte* last_page_end = memory_index[i - 1];
    uint next_page_start_id = i;
    while (memory_index[next_page_start_id] == MEMORY_EMPTY) { ++next_page_start_id; }
    // verify
    if (memory_index[next_page_start_id] - last_page_end > size)
    {
      // allocate
      memory_index[i] = last_page_end + 1;
      memory_index[i + 1] = memory_index[i] + size;
      return (void*) memory_index[i];
    }
  }
}

// free allocated memory
void kfree(void* memory)
{
  uint id = 0;
  while (memory_index[id] != memory) { id += 2; }
  memory_index[id] = MEMORY_EMPTY;
  memory_index[id + 1] = MEMORY_EMPTY;
}

// initializes kernel memory pointer -> allows for kmalloc() calls
void memory_init()
{
  memory_index[0] = (byte*) KERNEL_MEMORY_OFFSET_START;
  memory_index[1] = (byte*) KERNEL_MEMORY_OFFSET_START;
  for (uint i = 2 /* we dont want to overwrite KERNEL_MEMORY_OFFSET_START*/; i < sizeof(memory_index); ++i)
  {
    memory_index[i] = MEMORY_EMPTY;
  }
}

// copy memory
void memcpy(byte* dest, byte* src, uint32_t size)
{
  for (uint32_t i = 0; i < size; ++i)
  {
    dest[i] = src[i];
    ++i;
  }
}
