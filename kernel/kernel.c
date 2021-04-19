#define KERNEL_MEMORY_OFFSET 0x10000

#include "../lib/type.h"
#include "../lib/string.h"
#include "../drivers/display.h"
#include "messages.h"
#include "mem.h"

void init()
{
	kprints(KERNEL_INIT);
	kminit();
	kprints(KERNEL_INIT_DONE);
}

void main()
{
	// init
	knewline();
	kprints(KERNEL_ENTERED);
	init();
	kprints(KERNEL_WELCOME);
	// do
}
