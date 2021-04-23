void ksh_interpret(char* command)
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
}

void ksh_start()
{
  char c [31];
  while (true)
  {
    kprintc('$');
    kinputs(c);
    ksh_interpret(c);
  }
}
