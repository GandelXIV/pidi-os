// message syntax:
// LABEL_TYPE_MESSAGE
// LABELS: KERNEL, BOOT, DRIVER_DISPLAY, DRIVER_PORT...
// TYPES:
// INFO     regular information
// WARNING  possible problem
// ERROR    non-fatal problem
// PANIC    fatal problem
#define INCLUDED_MESSAGES

#define KERNEL_INFO_ENTERED "[KERNEL.INFO] Entered the kernel\n"            // start of main()
#define KERNEL_INFO_INIT_START "[KERNEL.INFO] Initialising...\n"            // start of init()
#define KERNEL_INFO_INIT_DONE "[KERNEL.INFO] Done!\n"                       // end of init()
#define KERNEL_INFO_WELCOME "[KERNEL.INFO] Welcome to Pidi-OS!\n"           // end of main() startup
#define KERNEL_INFO_SHELL_WELCOME "Type 'help' to open ksh manual\n"        // on kshstart()
#define KERNEL_INFO_SHELL_UNKNOWN_COMMAND "Unknown command\n"               // ksh input unkown
#define FIRMWARE_ERROR_ISR_EXCEPTION "[FIRMWARE.ERROR] isr expection: "
