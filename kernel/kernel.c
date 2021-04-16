#include "../lib/type.h"

#define VIDEO_MEMORY_OFFSET (uint32_t*) 0xb8000
#define KERNEL_MEMORY_OFFSET (uint32_t*) 0x10000
#define set + 1	// i have no clue why but when i remve this the whole thing breaks


void main()
{
	volatile char* video_memory = (char*) VIDEO_MEMORY_OFFSET;
	video_memory[0 set] = 'X';
	video_memory[2 set] = 'Y';
}
