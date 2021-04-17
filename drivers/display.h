#include "../lib/type.h"
#define VIDEO_MEMORY_OFFSET (uint*) 0xb8000
#define WHITE_ON_BLACK 0x0f
#define DISPLAY_WIDTH 80
#define DISPLAY_HEIGHT 25
#define INIT_VIDEO volatile char* video_memory = (volatile char*) VIDEO_MEMORY_OFFSET;

void display_char(char character, uint position, byte color);
void display_simple_print(char* string, uint buffer);
void display_clear();
