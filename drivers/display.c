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

// print char to cursor with color
void kcprintc(char character, char color)
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
    video_memory[cursor + 1] = color;
		set_cursor_offset(cursor + 2);
  }
}

// print char to cursor with default color
void kprintc(char character)
{
	kcprintc(character, DEFAULT_COLOR);
}

// print string to cursor with color
void kcprints(char* text, char color)
{
	while (*text != 0)
	{
		kcprintc(*text, color);
		++text;
	}
}

// print string to cursor with default color
void kprints(char* text)
{
	while (*text != 0)
	{
		kprintc(*text);
		++text;
	}
}

// copy a display row over another
void rowcpy(uint dest, uint src)
{
  INIT_VIDEO;
  // get row offset
  char* dest_offset = get_offset(0, dest) + video_memory;
  char* src_offset = get_offset(0, src) + video_memory;
  // use the offset in memcpy
  for (uint32_t i = 0; i < DISPLAY_WIDTH; ++i)
  {
    dest_offset[i] = src_offset[i];
    ++i;
  }
}

// scrol display by 1 row up
void kscroll()
{
  for (uint row = 1; row < DISPLAY_HEIGHT; ++row)
  {
    rowcpy(row - 1, row); // copy the current row to the last (row - 1)
  }
  uint cursor_offset = get_cursor_offset();
  uint cursor_offset_row = get_offset_row(cursor_offset);
  set_cursor_position( 0, cursor_offset_row - 1);
}

// called when display should scroll
void do_scroll()
{
  // kclear_display();
  kscroll();
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
