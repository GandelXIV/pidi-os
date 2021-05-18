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

#ifndef INCLUDED_KMSG
#include "kmsg.h"
#endif

#ifndef INCLUDED_MEM
#include "mem.h"
#endif

#ifndef INCLUDED_KSH
#include "ksh.h"
#endif

#ifndef INCLUDED_SMBIOS
#include "../firmware/smbios.h"
#endif

static bool kernel_running;


void main()
{
	// init
	kinfo(KERNEL_INFO_ENTERED);
	kinfo(KERNEL_INFO_INIT_START);
	kernel_running = true;					// start kernel loop
	display_theme(DISPLAY_THEME);	  // set display theme
	memory_init();									// init kernel memory for kmalloc()
	isr_install();									// set all isr handlers
	keyboard_init();								// nothing yet
	kmalloc(2);											// dont touch this...
	smbios_init();
	kinfo(KERNEL_INFO_INIT_DONE);
	kinfo(KERNEL_INFO_WELCOME);
	// main
	#include "debug.h" // this file is build on first compilation
	KERNEL_STARTUP
	while (kernel_running)
	{

	}
}
