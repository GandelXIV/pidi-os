#define KERNEL_MEMORY_OFFSET 0x10000

#include "../lib/type.h"
#include "../lib/string.h"
#include "../lib/conv.h"
#include "../drivers/display.h"
#include "messages.h"
#include "mem.h"

void init()
{
	kprints(KERNEL_INFO_INIT_START);
	kdisplay_theme(WHITE_ON_BLUE);
	kminit();
	kprints(KERNEL_INFO_INIT_DONE);
}

void main()
{
	// init
	kprintnl();
	kprints(KERNEL_INFO_ENTERED);
	init();
	kprints_color(KERNEL_INFO_WELCOME, GREEN_ON_BLUE);
	// do
}
