
#define KERNEL_MEMORY_OFFSET (uint*) 0x10000

#include "../lib/type.h"
#include "../drivers/display.h"
#include "messages.h"

void main()
{
	knewline();
	kprints(KERNEL_WELCOME);
}
