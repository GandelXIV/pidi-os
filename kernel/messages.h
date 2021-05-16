// message syntax:
// LABEL_TYPE_MESSAGE
// LABELS: KERNEL, BOOT, DRIVER_DISPLAY, DRIVER_PORT...
// TYPES:
// INFO     regular information
// WARNING  possible problem
// ERROR    non-fatal problem
// PANIC    fatal problem
#define INCLUDED_MESSAGES

#define KERNEL_INFO_ENTERED "Entered the kernel\n"            // start of main()
#define KERNEL_INFO_INIT_START "Initialising...\n"            // start of init()
#define KERNEL_INFO_INIT_DONE "Done!\n"                       // end of init()
#define KERNEL_INFO_WELCOME "Welcome to Pidi-OS!\n"           // end of main() startup
#define KERNEL_INFO_SHELL_WELCOME "\n$$$$$$$\\  $$\\       $$\\ $$\\  $$$$$$\\   $$$$$$\\  \n$$  __$$\\ \\__|      $$ |\\__|$$  __$$\\ $$  __$$\\ \n$$ |  $$ |$$\\  $$$$$$$ |$$\\ $$ /  $$ |$$ /  \\__|\n$$$$$$$  |$$ |$$  __$$ |$$ |$$ |  $$ |\\$$$$$$\\  \n$$  ____/ $$ |$$ /  $$ |$$ |$$ |  $$ | \\____$$\\ \n$$ |      $$ |$$ |  $$ |$$ |$$ |  $$ |$$\\   $$ |\n$$ |      $$ |\\$$$$$$$ |$$ | $$$$$$  |\\$$$$$$  |\n\\__|      \\__| \\_______|\\__| \\______/  \\______/ \n\nType 'help' to open ksh manual\n"        // on kshstart()
#define KERNEL_INFO_SHELL_UNKNOWN_COMMAND "Unknown command\n"               // ksh input unkown
#define KERNEL_PANIC_MEMORY_INDEX_FULL "Kernel index is full!\nCAUSE: It seems that there have been too many memory pages allocated...\n" // when memory_index is full
#define KERNEL_PANIC_MEMORY_FULL "Kernel memory is full!\nCAUSE: The system ran out of RAM..."
#define FIRMWARE_ERROR_ISR_EXCEPTION "[FIRMWARE.ERROR] isr expection: "
