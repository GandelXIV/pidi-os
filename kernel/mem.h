#pragma once
#include "../lib/type.h"
#include "kmsg.h"
#include "config.h"

#define MEMORY_EMPTY 0x0

void* kmalloc(uint32_t size);
void kfree(void* memory);
void memory_init();
void memcpy(byte* dest, byte* src, uint32_t size);
uint32_t memory_usage();
uint32_t memory_usage_effective();
uint32_t memory_total();
