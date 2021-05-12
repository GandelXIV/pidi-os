#define KSH_OK 0x0
#define KSH_EXIT 0x1
#define KSH_INPUT_BUFFER 31

byte ksh_interpret(char* command)
{
  int NoOfOwnCmds = 10, i, switchOwnArg = 0;
  char* ListOfOwnCmds[NoOfOwnCmds];

  ListOfOwnCmds[0] = "help\n";
  ListOfOwnCmds[1] = "echo\n";
  ListOfOwnCmds[2] = "wipe\n";
  ListOfOwnCmds[3] = "pidiver\n";
  ListOfOwnCmds[4] = "mem\n";
  ListOfOwnCmds[5] = "blue\n";
  ListOfOwnCmds[6] = "cyan\n";
  ListOfOwnCmds[7] = "gray\n";
  ListOfOwnCmds[8] = "hacker\n";
  ListOfOwnCmds[9] = "exit\n";

  for (i = 0; i < NoOfOwnCmds; i++) {
    if (strcmp(command, "\n") == true) {}
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
      kprints("help     prints this message\n");
      kprints("echo     prints 'echo' to the display\n");
      kprints("wipe     cleans screen\n");
      kprints("pidiver  get kernel version\n");
      kprints("mem      get allocated memory usage\n");
      kprints("blue     changes the theme to white on blue\n");
      kprints("cyan     changes the theme to white on cyan\n");
      kprints("gray     changes the theme to gray on black\n");
      kprints("exit     exit kernel shell\n");
      break;
    case 2:
      kprints("Hello World!\n");
      break;
    case 3:
      display_clear();
      break;
    case 4:
      kprints("Pidi OS\n");
      kprints("Version: 0.1.1\n");
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
