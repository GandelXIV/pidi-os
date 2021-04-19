#include "display.h"
#include "port.h"

uint get_offset(uint column, uint row) { return 2 * (row * DISPLAY_WIDTH + column); }
uint get_offset_row(uint offset) { return offset / (2 * DISPLAY_WIDTH); }
uint get_offset_column(uint offset) { return (offset - (get_offset_row(offset)*2*DISPLAY_WIDTH))/2; }

uint get_cursor_offset()
{
    port_byte_out(REG_DISPLAY_CTRL, 14);
    uint offset = port_byte_in(REG_DISPLAY_DATA) << 8;
    port_byte_out(REG_DISPLAY_CTRL, 15);
    offset += port_byte_in(REG_DISPLAY_DATA);
    return offset * 2;
}

void set_cursor_offset(uint offset)
{
    offset /= 2;
    port_byte_out(REG_DISPLAY_CTRL, 14);
    port_byte_out(REG_DISPLAY_DATA, (byte) (offset >> 8));
    port_byte_out(REG_DISPLAY_CTRL, 15);
    port_byte_out(REG_DISPLAY_DATA, (byte) (offset & 0xff));
}

void set_cursor_position(uint column, uint row) { set_cursor_offset(get_offset(column, row)); }

// draws character at specific offset
void display_char(char character, uint offset, byte color)
{
	INIT_VIDEO
	video_memory[offset*2] = character;
	video_memory[offset*2 + 1] = color;
}

// print char to cursor
void kprintc(char character)
{
	INIT_VIDEO
	uint cursor = get_cursor_offset();
	if (character == '\n')
	{
		knewline();
	}
  else
  {
    video_memory[cursor] = character;
		set_cursor_offset(cursor + 2);
  }
}

// print string to cursor
void kprints(char* text)
{
	while (*text != 0)
	{
		kprintc(*text);
		++text;
	}
}

// called when display should be cleared
void do_scroll()
{
  kclear_display();
}

// prints a newline, equivalent to kprintc('\n')
void knewline()
{
  uint cursor_offset = get_cursor_offset();
  uint cursor_offset_row = get_offset_row(cursor_offset);
  set_cursor_position( 0, cursor_offset_row + 1);
  if (cursor_offset_row > DISPLAY_HEIGHT) do_scroll();
}

// clear display by printing a LOT of spaces!
void kclear_display()
{
	for (uint i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; ++i)
	{
		display_char(' ', i, WHITE_ON_BLACK);
	}
	set_cursor_offset(0);
}
