void ksh_interpret(char* command)
{
  if (command[0] == '\n') {}
  else if (strcmp(command, "echo\n"))
  {
    kprints("echo\n");
  }
  else if (strcmp(command, "blue\n"))
  {
    kdisplay_theme(WHITE_ON_BLUE);
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
