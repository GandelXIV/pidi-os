#define INCLUDED_MEM
#ifndef INCLUDED_TYPE
#include "../lib/type.h"
#endif

#define KERNEL_MEMORY_OFFSET_START 0x10000
#define KERNEL_MEMORY_OFFSET_END	0xffffffff

#define MEMORY_INDEX_BASE_SIZE 1000
#define MEMORY_EMPTY 0x0
#define MEMORY_INDEX_END 0x1

void* kmalloc(uint32_t size);
void kfree(void* memory);
void memory_init();
void memcpy(byte* dest, byte* src, uint32_t size);
uint32_t memory_usage();
uint32_t memory_usage_effective();
