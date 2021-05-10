// config
#define DISPLAY_THEME GRAY_ON_BLACK

#ifndef INCLUDED_TYPE
#include "../lib/type.h"
#endif
#ifndef INCLUDED_STRING
#include "../lib/string.h"
#endif
#ifndef INCLUDED_CONV
#include "../lib/conv.h"
#endif

#include "../firmware/isr.h"

#include "messages.h"
#include "mem.h"
#include "io.h"
#include "ksh.h"

static bool kernel_running;

void kpanic(char* msg)
{
	kprints(msg);
	while (true) {}		// infinite loop
}

void main()
{
	// init
	kprints(KERNEL_INFO_ENTERED);
	kprints(KERNEL_INFO_INIT_START);
	kernel_running = true;					// start kernel loop
	display_theme(DISPLAY_THEME);	  // set display theme
	memory_init();									// init kernel memory for kmalloc()
	isr_install();									// set all isr handlers
	keyboard_init();								// nothing yet
	kprints(KERNEL_INFO_INIT_DONE);
	kprints(KERNEL_INFO_WELCOME);
	// main
	#include "debug.h" // this file is build on first compilation
	ksh_start();
	while (kernel_running)
	{

	}
}
