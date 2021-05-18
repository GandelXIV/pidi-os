#define INCLUDED_KSH

#ifndef INCLUDED_TYPE
#include "../lib/type.h"
#endif

#ifndef INCLUDED_STRING
#include "../lib/string.h"
#endif

#ifndef INCLUDED_COLOR
#include "../drivers/display_color.h"
#endif

#ifndef INCLUDED_MEM
#include "mem.h"
#endif

#ifndef INCLUDED_KMSG
#include "kmsg.h"
#endif

#ifndef INCLUDED_IO
#include "io.h"
#endif

#ifndef INCLUDED_SMBIOS
#include "../firmware/smbios.h"
#endif

#ifndef INCLUDED_VERSION
#include "version.h"
#endif

#define KSH_OK 0x0
#define KSH_EXIT 0x1
#define KSH_INPUT_BUFFER 31

byte ksh_interpret(char* command)
{
  int switchOwnArg = -1;
  char* ListOfOwnCmds [] = {
    "help\n",
    "echo\n",
    "wipe\n",
    "pidiver\n",
    "memstat\n",
    "theme-blue\n",
    "theme-cyan\n",
    "theme-gray\n",
    "hacker\n",
    "exit\n",
    "memtest\n",
    "theme-default\n",
    "neofetch\n"
  };

  for (int i = 0; i < sizeof(ListOfOwnCmds) / sizeof(char*); i++) {
    if (strcmp(command, "\n") == true) {switchOwnArg = 0;}
    else if (strcmp(command, ListOfOwnCmds[i]) == true) {
      switchOwnArg = i + 1;
      break;
    }
  }

  switch (switchOwnArg) {
    case 0:
      break;
    case 1:
      kprints("COMMANDS:\n");
      kprints("help           prints this message\n");
      kprints("echo           prints 'echo' to the display\n");
      kprints("wipe           cleans screen\n");
      kprints("pidiver        get kernel version\n");
      kprints("memstat        get allocated memory usage\n");
      kprints("memtest        allocate memory for test\n");
      kprints("theme-blue     changes the theme to white on blue\n");
      kprints("theme-cyan     changes the theme to white on cyan\n");
      kprints("theme-gray     changes the theme to gray on black\n");
      kprints("theme-default  changes the theme back to default\n");
      kprints("exit            exit kernel shell\n");
      break;
    case 2:
      kprints("Hello World!\n");
      break;
    case 3:
      display_clear();
      break;
    case 4:
      kprints("Pidi OS\n");
      kprints("Version: ");
      kprints(OS_VERSION);
      kprintc('\n');
      break;
    case 5:
      kprints("Memory usage:");
      kprints("\ntotal: ");
      kprintu32(memory_usage());
      kprints("\neffective: ");
      kprintu32(memory_usage_effective());
      kprintc('\n');
      break;
    case 6:
      display_theme(WHITE_ON_BLUE);
      break;
    case 7:
      display_theme(WHITE_ON_CYAN);
      break;
    case 8:
      display_theme(GRAY_ON_BLACK);
      break;
    case 9:
      display_theme(GREEN_ON_BLACK);
      kprints_color("You are hacker now!\n", RED_ON_WHITE);
      break;
    case 10:
      display_clear();
      return KSH_EXIT;
    case 11:
      kmalloc(1);
      break;
    case 12:
      display_theme(DISPLAY_THEME);
      break;
    case 13:
      kprints("OS: Pidi OS ");
      kprints(OS_VERSION);
      kprintc('\n');
      kprints("BIOS name: ");
      kprints(smbios_get_bios_name());
      kprintc('\n');
      kprints("BIOS version:");
      kprints(smbios_get_bios_version());
      kprintc('\n');
      break;
    default:
      kprints(KERNEL_INFO_SHELL_UNKNOWN_COMMAND);
      break;
  }
  return KSH_OK;
}

void ksh_start()
{
  char c [KSH_INPUT_BUFFER];
  for (uint i = 0; i < KSH_INPUT_BUFFER; ++i)
  {
    c[i] = (char) 0;
  }
  byte response;
  kprints(KERNEL_INFO_SHELL_WELCOME);
  while (true)
  {
    kprintc('$');
    kinputs(c);
    response = ksh_interpret(c);
    if (response == KSH_EXIT)
    {
      break;
    }
    strcls(c);
  }
}
