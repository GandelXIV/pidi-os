#define INIT_VIDEO_MEMORY volatile unsigned char* video_memory = (char*) VIDEO_MEMORY_OFFSET;


void display_putc(char character, uint pos)
{
	INIT_VIDEO_MEMORY
	video_memory[pos + 1] = character;
}

