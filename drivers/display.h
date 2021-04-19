#include "../lib/type.h"
#define VIDEO_MEMORY_OFFSET (uint*) 0xb8000

// config
#define DISPLAY_WIDTH 80
#define DISPLAY_HEIGHT 25
#define DEFAULT_COLOR GRAY_ON_BLACK // grey on black (see in drivers/color.h)

#include "color.h"

// code
#define INIT_VIDEO char* video_memory = (char*) VIDEO_MEMORY_OFFSET;

// PORTs
#define REG_DISPLAY_CTRL 0x3d4
#define REG_DISPLAY_DATA 0x3d5

// kernel API
void kprints(char* text);
void kcprints(char* text, char color);
void kprintc(char character);
void kcprintc(char character, char color);
void kclear_display();
void knewline();
void copyrow(uint dest, uint src);
void kscroll();
