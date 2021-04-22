#define KERNEL_MEMORY_OFFSET 0x10000

#ifndef INCLUDED_TYPE
#include "../lib/type.h"
#endif
#ifndef INCLUDED_STRING
#include "../lib/string.h"
#endif
#ifndef INCLUDED_CONV
#include "../lib/conv.h"
#endif

#include "messages.h"
#include "mem.h"
#include "io.h"
#include "../drivers/keyboard.h"


void init()
{
	kprints(KERNEL_INFO_INIT_START);
	// do
	kdisplay_theme(BLACK_ON_CYAN);
	kminit();
	kkeyboard_init();
	// done
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
	while (1) { kprintc(kinputc()); }
}
