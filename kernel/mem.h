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
