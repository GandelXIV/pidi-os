void display_test(char character)
{
	volatile char* video_memory = (char*) VIDEO_MEMORY_OFFSET;
	video_memory[0 set] = character;
}
