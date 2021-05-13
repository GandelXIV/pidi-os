#include "../lib/type.h"

#define KSH_OK 0x0
#define KSH_EXIT 0x1
#define KSH_INPUT_BUFFER 31

byte ksh_interpret(char* command);
void ksh_start();
