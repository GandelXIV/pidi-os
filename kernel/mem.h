#define INCLUDED_MEM "cookie"
#ifndef INCLUDED_TYPE
#include "../lib/type.h"
#endif

#define KERNEL_MEMORY_OFFSET_START 0x10000
#define KERNEL_MEMORY_OFFSET_END	0xffffffff

#define MEMORY_EMPTY 0x0


void* kmalloc(uint32_t size);
void kfree(void* memory);
void memory_init();
void memcpy(byte* dest, byte* src, uint32_t size);
