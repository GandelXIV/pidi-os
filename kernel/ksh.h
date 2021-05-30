#pragma once
#include "../lib/type.h"
#include "../lib/string.h"
#include "../drivers/display_color.h"
#include "mem.h"
#include "kmsg.h"
#include "io.h"
#include "../firmware/smbios.h"
#include "version.h"

char* theme;

#include "advanced_cmds/neofetch.h"
#include "advanced_cmds/list_files.h"
#include "advanced_cmds/read_file.h"

#define KSH_OK 0x0
#define KSH_EXIT 0x1
#define KSH_INPUT_BUFFER 31

byte ksh_interpret(char* command)
{
  int switchOwnArg = -1;
  char* ListOfOwnCmds [] = {
    "help",
    "echo",
    "wipe",
    "pidiver",
    "memstat",
    "theme-blue",
    "theme-cyan",
    "theme-gray",
    "hacker",
    "exit",
    "memtest",
    "theme-default",
    "neofetch",
    "ls",
    "mk",
    "rm",
    "in"
  };

  for (int i = 0; i < sizeof(ListOfOwnCmds) / sizeof(char*); i++) {
    if (*command == 0) {switchOwnArg = 0;}
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
      kprints("neofetch       show info about your system\n");
      kprints("exit           exit kernel shell\n");
      kprints("ls             list all files\n");
      kprints("mk             create new file\n");
      kprints("rm             delete file\n");
      kprints("in             read file content\n");
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
      theme = "WHITE_ON_BLUE";
      break;
    case 7:
      display_theme(WHITE_ON_CYAN);
      theme = "WHITE_ON_CYAN";
      break;
    case 8:
      display_theme(GRAY_ON_BLACK);
      theme = "GRAY_ON_BLACK";
      break;
    case 9:
      display_theme(GREEN_ON_BLACK);
      theme = "GREEN_ON_BLACK";
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
      theme = "GREEN_ON_BLACK";
      break;
    case 13:
      ksh_neofetch();
      break;
    case 14:
      ksh_list_files();
      break;
    case 15:
      kprints("Enter file name: ");
      char file_to_make [255];
      kinputs(file_to_make);
      if (file_make(file_to_make) == FILE_ALREADY_EXISTS)
      {
        kprints("File already exists!\n");
      }
      break;
    case 16:
      kprints("Enter file name: ");
      char file_to_remove [255];
      kinputs(file_to_remove);
      if (file_remove(file_to_remove) == FILE_NOT_FOUND)
      {
        kprints("File not found!\n");
      }
      break;
    case 17:
      ksh_read_file();
      break;
    default:
      kprints(KERNEL_INFO_SHELL_UNKNOWN_COMMAND);
      break;
  }
  return KSH_OK;
}

void ksh_start()
{
  theme = "GREEN_ON_BLACK";
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
