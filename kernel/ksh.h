#define KSH_OK 0x0
#define KSH_EXIT 0x1

byte ksh_interpret(char* command)
{
  if (command[0] == '\n') {}
  else if (strcmp(command, "echo\n"))
  {
    kprints("Hello World!\n");
  }
  else if (strcmp(command, "blue\n"))
  {
    display_theme(WHITE_ON_BLUE);
  }
  else if (strcmp(command, "help\n"))
  {
    kprints("COMMANDS:\n");
    kprints("help    prints this message\n");
    kprints("echo    prints 'echo' to the display\n");
    kprints("wipe    cleans screen\n");
    kprints("pidi    get kernel version\n");
    kprints("mem     get allocated memory usage\n");
    kprints("blue    changes the theme to white on blue\n");
    kprints("cyan    changes the theme to white on cyan\n");
    kprints("gray    changes the theme to gray on black\n");
    kprints("exit    exit kernel shell\n");
  }
  else if (strcmp(command, "cyan\n"))
  {
    display_theme(WHITE_ON_CYAN);
  }
  else if (strcmp(command, "exit\n"))
  {
    display_clear();
    return KSH_EXIT;
  }
  else if (strcmp(command, "wipe\n"))
  {
    display_clear();
  }
  else if (strcmp(command, "gray\n"))
  {
    display_theme(GRAY_ON_BLACK);
  }
  else if (strcmp(command, "pidi\n"))
  {
    kprints("Pidi OS\n");
    kprints("Version: 0.1.1\n");
  }
  else if (strcmp(command, "mem\n"))
  {
    kprints("Memory usage:");
    kprints("\ntotal: ");
    kprintu32(memory_usage());
    kprints("\neffective: ");
    kprintu32(memory_usage_effective());
    kprintc('\n');
  }
  else
  {
    kprints("Unknown command\n");
  }
  return KSH_OK;
}

void ksh_start()
{
  char c [31];
  byte response;
  kprints("Type 'help' to open ksh manual\n");
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
