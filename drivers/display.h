#define INIT_VIDEO volatile char* video_memory = (volatile char*) VIDEO_MEMORY_OFFSET;

void display_char(char character, uint position)
{
	INIT_VIDEO
	video_memory[position*2] = character;
}
