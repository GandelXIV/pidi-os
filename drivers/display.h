#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4
#define DISPLAY_WIDTH 80
#define DISPLAY_HEIGHT 25
#define INIT_VIDEO volatile char* video_memory = (volatile char*) VIDEO_MEMORY_OFFSET;

void display_char(char character, uint position, byte color)
{
	INIT_VIDEO
	video_memory[position*2] = character;
	video_memory[position*2 + 1] = color;
}

void display_simple_print(char* string, uint buffer)
{
	for (uint i = 0; i < buffer; ++i)
	{
		display_char(string[i], i, WHITE_ON_BLACK);
	}
}

void display_clear()
{
	for (uint i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; ++i)
	{
		display_char(' ', i, WHITE_ON_BLACK);
	}
}
