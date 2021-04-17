#include "display.h"
#include "port.h"

uint get_offset(uint col, uint row) { return 2 * (row * DISPLAY_WIDTH + col); }
uint get_offset_row(uint offset) { return offset / (2 * DISPLAY_WIDTH); }

uint get_cursor_offset() {
    port_byte_out(REG_DISPLAY_CTRL, 14);
    uint offset = port_byte_in(REG_DISPLAY_DATA) << 8;
    port_byte_out(REG_DISPLAY_CTRL, 15);
    offset += port_byte_in(REG_DISPLAY_DATA);
    return offset * 2;
}

void set_cursor_offset(uint offset) {
    offset /= 2;
    port_byte_out(REG_DISPLAY_CTRL, 14);
    port_byte_out(REG_DISPLAY_DATA, (byte) (offset >> 8));
    port_byte_out(REG_DISPLAY_CTRL, 15);
    port_byte_out(REG_DISPLAY_DATA, (byte) (offset & 0xff));
}

void display_char(char character, uint offset, byte color)
{
	INIT_VIDEO
	video_memory[offset*2] = character;
	video_memory[offset*2 + 1] = color;
}

void kprintc(char character)
{
	INIT_VIDEO
	uint cursor = get_cursor_offset();
	if (character != '\n')
	{
		video_memory[cursor] = character;
		set_cursor_offset(cursor + 2);
	}
	else
	{
		knewline();
	}
}

void kprints(char* text)
{
	while (*text != 0)
	{
		kprintc(*text);
		++text;
	}
}

void knewline()
{
  set_cursor_offset(get_offset(0, get_offset_row(get_cursor_offset()) + 1));
}

void kclear_display()
{
	for (uint i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; ++i)
	{
		display_char(' ', i, WHITE_ON_BLACK);
	}
	set_cursor_offset(0);
}
