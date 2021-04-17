
#define KERNEL_MEMORY_OFFSET 0x10000

#include "../lib/type.h"
#include "../drivers/display.h"
#include "messages.h"
#include "mem.h"

void init()
{
	kprints(KERNEL_INIT);
	kminit();
}

void main()
{
	// init
	knewline();
	kprints(ENTERED_KERNEL);
	init();
	kprints(KERNEL_WELCOME);
}
