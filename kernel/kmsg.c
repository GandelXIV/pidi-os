#include "kmsg.h"
#include "io.h"
#include "../drivers/display_color.h"


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
  kprints_color("[PANIC] ", RED_ON_BLACK);
  kprints_color(msg, RED_ON_BLACK);
  while (1) { /* infinite loop */ }
}
