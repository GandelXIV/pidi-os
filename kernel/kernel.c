#pragma once

#include "config.h"
#include "io.h"
#include "kmsg.h"
#include "mem.h"
#include "ksh.h"
#include "../cpu/smbios.h"
#include "../fs/fscore.h"
#include "../lib/type.h"
#include "../lib/rand.h"

static bool kernel_running;


void main()
{
	// init
	kinfo(KERNEL_INFO_ENTERED);
	kinfo(KERNEL_INFO_INIT_START);
	kernel_running = true;
	display_theme(DISPLAY_THEME);
	memory_init();
	keyboard_init();
	smbios_init();
	display_init();
	fsinit();
	rand_init();
	kinfo(KERNEL_INFO_INIT_DONE);
	kinfo(KERNEL_INFO_WELCOME);
	// main
	#include "debug.h" // this file is created by ./configure
	KERNEL_STARTUP
	while (kernel_running)
	{
		KERNEL_UPDATE
	}
}
