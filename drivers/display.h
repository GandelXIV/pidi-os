#define INCLUDED_DISPLAY "cookie"
#ifndef INCLUDED_TYPE
#include "../lib/type.h"
#endif
#define VIDEO_MEMORY_OFFSET (uint*) 0xb8000

// config
#define DISPLAY_WIDTH 80
#define DISPLAY_HEIGHT 25
#define DISPLAY_SCROLL_DEBUG -2

// color
#define TRANSPARENT 0x00
#include "color.h"

// code
#define INIT_VIDEO char* video_memory = (char*) VIDEO_MEMORY_OFFSET;

// PORTs
#define REG_DISPLAY_CTRL 0x3d4
#define REG_DISPLAY_DATA 0x3d5

// kernel API
void kprints(char* text);
void kprints_color(char* text, char color);
void kprintc(char character);
void kprintc_color(char character, char color);
void kdisplay_clear();
void kprintnl();
void kdisplay_scroll();
void kdisplay_theme(char color);
void kdisplay_deletec();
