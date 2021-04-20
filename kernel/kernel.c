#define KERNEL_MEMORY_OFFSET 0x10000

#include "../lib/type.h"
#include "../lib/string.h"
#include "../drivers/display.h"
#include "messages.h"
#include "mem.h"

void init()
{
	kprints(KERNEL_INFO_INIT);
	kminit();
	kprints(KERNEL_INFO_INIT_DONE);
}

void main()
{
	// init
	knewline();
	kprints(KERNEL_INFO_ENTERED);
	ktheme_set(BLACK_ON_CYAN);
	init();
	kprints_color(KERNEL_INFO_WELCOME, BLACK_ON_CYAN);
	// do
}
