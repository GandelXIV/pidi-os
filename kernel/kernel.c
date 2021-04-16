#define VIDEO_MEMORY_OFFSET (uint*) 0xb8000
#define KERNEL_MEMORY_OFFSET (uint*) 0x10000
#define set + 1	// i have no clue why but when i remve this the whole thing breaks

#include "../lib/type.h"
#include "../drivers/display.h"


void main()
{
	display_putc('X', 0);
}
