#define VIDEO_MEMORY_OFFSET (uint*) 0xb8000
#define KERNEL_MEMORY_OFFSET (uint*) 0x10000

#include "../lib/type.h"
#include "../drivers/display.h"

void main()
{
	char* text;
	text = "XYZ";
	display_char(text[0], 0);
	display_char(text[1], 1);
	display_char(text[2], 2);
}
