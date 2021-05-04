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

#include "../firmware/isr.h"

#include "messages.h"
#include "mem.h"
#include "io.h"
#include "ksh.h"

#define DISPLAY_THEME GRAY_ON_BLACK

void test_interrupts()
{
	// test the new interrupts
	__asm__ __volatile__("int $2");
	__asm__ __volatile__("int $3");
}

void init()
{
	kprints(KERNEL_INFO_INIT_START);
	// do
	display_theme(DISPLAY_THEME);	  // set display theme
	memory_init();									// init kernel memory for kmalloc()
	isr_install();									// set all isr handlers
	keyboard_init();								// nothing yet
	// done
	kprints(KERNEL_INFO_INIT_DONE);
}

void main()
{
	// init
	kprints(KERNEL_INFO_ENTERED);
	init();
	kprints(KERNEL_INFO_WELCOME);
	// do
	ksh_start();
}
