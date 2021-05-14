#include "kmsg.h"

void kinfo(char* msg)
{
  kprints("[KERNEL.INFO] ");
  kprints(msg);
}

void kwarning(char* msg)
{
  kprints("[KERNEL.WARNING] ");
  kprints(msg);
}

void kerror(char* msg)
{
  kprints("[KERNEL.ERROR] ");
  kprints(msg);
}

void kpanic(char* msg)
{
  kprints("[KERNEL.PANIC] ");
  kprints(msg);
  while (1) { /* infinite loop */ }
}
