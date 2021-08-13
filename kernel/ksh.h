#pragma once
#include "../lib/type.h"
#include "../lib/string.h"
#include "../drivers/display_color.h"
#include "mem.h"
#include "kmsg.h"
#include "io.h"
#include "../cpu/smbios.h"
#include "version.h"

char* theme;

#include "advanced_cmds/neofetch.h"
#include "advanced_cmds/list_files.h"
#include "advanced_cmds/read_file.h"
#include "advanced_cmds/write_to_file.h"
#include "advanced_cmds/make_file.h"
#include "advanced_cmds/remove_file.h"

#define KSH_OK 0x0
#define KSH_EXIT 0x1
#define KSH_INPUT_BUFFER 31

byte ksh_interpret(char* command)
{
  if (!*command)
  {
    return KSH_OK;
  }
  else if (strcmp(command, "help"))
  {
    #include "advanced_cmds/help.h"
  }
  else if (strcmp(command, "echo"))
  {
    kprints("echo\n");
  }
  else if (strcmp(command, "wipe"))
  {
    display_clear();
  }
  else if (strcmp(command, "version"))
  {
    kprints("Pidi OS\n");
    kprints("Version: ");
    kprints(OS_VERSION);
    kprintc('\n');
  }
  else if (strcmp(command, "memstat"))
  {
    kprints("Memory usage:");
    kprints("\ntotal: ");
    kprintu32(memory_usage());
    kprints("\neffective: ");
    kprintu32(memory_usage_effective());
    kprintc('\n');
  }
  else if (strcmp(command, "theme-blue"))
  {
    display_theme(WHITE_ON_BLUE);
    theme = "WHITE_ON_BLUE";
  }
  else if (strcmp(command, "theme-cyan"))
  {
    display_theme(WHITE_ON_CYAN);
    theme = "WHITE_ON_CYAN";
  }
  else if (strcmp(command, "theme-gray"))
  {
    display_theme(GRAY_ON_BLACK);
    theme = "GRAY_ON_BLACK";
  }
  else if (strcmp(command, "hacker"))
  {
    display_theme(GREEN_ON_BLACK);
    theme = "GREEN_ON_BLACK";
    kprints_color("You are hacker now!\n", RED_ON_WHITE);
  }
  else if (strcmp(command, "exit"))
  {
    display_clear();
    return KSH_EXIT;
  }
  else if (strcmp(command, "memtest"))
  {
      kmalloc(1);
  }
  else if (strcmp(command, "theme-default"))
  {
    display_theme(DISPLAY_THEME);
    theme = "DEFAULT_THEME";
  }
  else if (strcmp(command, "neofetch"))
  {
    ksh_neofetch();
  }
  else if (strcmp(command, "ls"))
  {
    ksh_list_files();
  }
  else if (strcmp(command, "mk"))
  {
    ksh_make_file();
  }
  else if (strcmp(command, "rm"))
  {
    ksh_remove_file();
  }
  else if (strcmp(command, "in"))
  {
    ksh_read_file();
  }
  else if (strcmp(command, "to"))
  {
    ksh_write_to_file();
  }
  else if (strcmp(command, "random"))
  {
    kprintu(rand() % 100);  // random number between 0-100
    kprintc('\n');
  }
  else
  {
    kprints(KERNEL_INFO_SHELL_UNKNOWN_COMMAND);
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
