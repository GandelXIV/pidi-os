#pragma once

#include "../cpu/port.h"
#include "../lib/type.h"
#include "../kernel/config.h"

#define VIDEO_MEMORY_OFFSET (uint*) 0xb8000

// config
#define DISPLAY_WIDTH 80
#define DISPLAY_HEIGHT 25
// dont touch these
#define DISPLAY_SCROLL_DEBUG 80
#define DISPLAY_SCROLL_DETECTION_DEBUG -2

// color
#define TRANSPARENT 0x00
#include "display_color.h"

// code
#define INIT_VIDEO char* video_memory = (char*) VIDEO_MEMORY_OFFSET;

// kernel API
void kprintc(char character);
void kprintc_color(char character, char color);
void kprint(char* text, uint32_t depth);
void kprint_color(char* text, uint32_t depth, byte color);
void display_clear();
void display_scroll();
void display_theme(char color);
void display_deletec();
void display_init();
void set_cursor_position(uint column, uint row);
