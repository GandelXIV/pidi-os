// config
#define DISPLAY_THEME GRAY_ON_BLACK
#define KERNEL_MEMORY_OFFSET 0x10000	// temporary
#define KERNEL_MEMORY_OFFSET_START 0x10000
#define KERNEL_MEMORY_OFFSET_END	0xffffffff

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


void test_interrupts()
{
	// test the new interrupts
	__asm__ __volatile__("int $2");
	__asm__ __volatile__("int $3");
}

void main()
{
	// init
	kprints(KERNEL_INFO_ENTERED);
	kprints(KERNEL_INFO_INIT_START);
	display_theme(DISPLAY_THEME);	  // set display theme
	memory_init();									// init kernel memory for kmalloc()
	isr_install();									// set all isr handlers
	keyboard_init();								// nothing yet
	kprints(KERNEL_INFO_INIT_DONE);
	kprints(KERNEL_INFO_WELCOME);
	// main
	#include "debug.h" // this file is build on first compilation
	ksh_start();
}
