#include "kmsg.h"
#include "io.h"

void kinfo(char* msg)
{
  kprints("[INFO] ");
  kprints(msg);
}

void kwarning(char* msg)
{
  kprints("[WARNING] ");
  kprints(msg);
}

void kerror(char* msg)
{
  kprints("[ERROR] ");
  kprints(msg);
}

void kpanic(char* msg)
{
  kprints("[PANIC] ");
  kprints(msg);
  while (1) { /* infinite loop */ }
}
