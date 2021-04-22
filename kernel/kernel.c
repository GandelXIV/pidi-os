#define KERNEL_MEMORY_OFFSET 0x10000

#include "../lib/type.h"
#include "../lib/string.h"
#include "messages.h"
#include "mem.h"
#include "io.h"

void init()
{
	kprints(KERNEL_INFO_INIT_START);
	kdisplay_theme(BLACK_ON_CYAN);
	kminit();
	kprints(KERNEL_INFO_INIT_DONE);
}

void main()
{
	// init
	kprintnl();
	kprints(KERNEL_INFO_ENTERED);
	init();
	kprints_color(KERNEL_INFO_WELCOME, PURPLE_ON_CYAN);
	// do
}
