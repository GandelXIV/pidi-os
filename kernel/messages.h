// message syntax:
// LABEL_TYPE_MESSAGE
// LABELS: KERNEL, BOOT, DRIVER_DISPLAY, DRIVER_PORT...
// TYPES:
// INFO     regular information
// WARNING  possible problem
// ERROR    non-fatal problem
// PANIC    fatal problem
#define KERNEL_INFO_ENTERED "Entered the kernel\n"         // start of main()
#define KERNEL_INFO_INIT_START "Initialising...\n"                  // start of init()
#define KERNEL_INFO_INIT_DONE "Done!\n"                       // end of init()
#define KERNEL_INFO_WELCOME "Welcome to Pidi-OS!\n"           // end of main() startup
