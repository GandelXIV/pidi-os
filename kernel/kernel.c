#pragma once
#include "config.h"
#include "../lib/type.h"
#include "io.h"
#include "../firmware/isr.h"
#include "kmsg.h"
#include "mem.h"
#include "ksh.h"
#include "../firmware/smbios.h"
#include "../fs/fscore.h"

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
	smbios_init();									// get hardware info
	display_init();									// init some display vars
	fsinit();												// init file system
	kinfo(KERNEL_INFO_INIT_DONE);
	kinfo(KERNEL_INFO_WELCOME);
	// main
	#include "debug.h" // this file is build on first compilation
	KERNEL_STARTUP
	while (kernel_running)
	{

	}
}
