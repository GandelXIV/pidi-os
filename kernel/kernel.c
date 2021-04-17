
#define KERNEL_MEMORY_OFFSET (uint*) 0x10000

#include "../lib/type.h"
#include "../drivers/display.h"

void main()
{
	kclear_display();
	char* text = "Hello\n";
	kprintc('X');
	kprintc('Y');
	kprints(text);
	kprints(text);
}
