#include "config.h"

#ifndef INCLUDED_TYPE
#include "../lib/type.h"
#endif

#ifndef INCLUDED_IO
#include "io.h"
#endif

#ifndef INCLUDED_ISR
#include "../firmware/isr.h"
#endif

#ifndef INCLUDED_COLOR
#include "../drivers/display_color.h"
#endif

#ifndef INCLUDED_MESSAGES
#include "messages.h"
#endif

#ifndef INCLUDED_MEM
#include "mem.h"
#endif

#ifndef INCLUDED_KSH
#include "ksh.h"
#endif

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
	kmalloc(2);											// dont touch this...
	kprints(KERNEL_INFO_INIT_DONE);
	kprints(KERNEL_INFO_WELCOME);
	// main
	#include "debug.h" // this file is build on first compilation
	KERNEL_STARTUP
	while (kernel_running)
	{

	}
}
