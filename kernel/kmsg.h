#define INCLUDED_KMSG

#ifndef INCLUDED_MESSAGES
#include "messages.h"
#endif

void kinfo(char* msg);
void kwarning(char* msg);
void kerror(char* msg);
void kpanic(char* msg);
