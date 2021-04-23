#define KSH_OK 0x0
#define KSH_EXIT 0x1

byte ksh_interpret(char* command)
{
  if (command[0] == '\n') {}
  else if (strcmp(command, "echo\n"))
  {
    #include "kshcmd/echo.h"
  }
  else if (strcmp(command, "blue\n"))
  {
    #include "kshcmd/blue.h"
  }
  else if (strcmp(command, "help\n"))
  {
    #include "kshcmd/help.h"
  }
  else if (strcmp(command, "cyan\n"))
  {
    #include "kshcmd/cyan.h"
  }
  else if (strcmp(command, "exit\n"))
  {
    #include "kshcmd/exit.h"
  }
  else if (strcmp(command, "wipe\n"))
  {
    #include "kshcmd/wipe.h"
  }
  return KSH_OK;
}

void ksh_start()
{
  char c [31];
  byte response;
  while (true)
  {
    kprintc('$');
    kinputs(c);
    response = ksh_interpret(c);
    if (response == KSH_EXIT)
    {
      break;
    }
  }
}
