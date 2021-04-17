#define VIDEO_MEMORY_OFFSET (uint*) 0xb8000
#define KERNEL_MEMORY_OFFSET (uint*) 0x10000

#include "../lib/type.h"
#include "../drivers/display.h"

void main()
{
	display_clear();
	char* text;
	text = "Hello";
	display_simple_print(text, 5);
}
