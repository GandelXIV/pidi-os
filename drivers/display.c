#include "display.h"
#include "../firmware/port.h"

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
  if (color != 0x00) { video_memory[offset*2 + 1] = color; }
}

// print char to cursor with color
void kprintc_color(char character, char color)
{
  INIT_VIDEO
	uint cursor = get_cursor_offset();
	if (character == '\n')
	{
		kprintnl();
	}
  else
  {
    video_memory[cursor] = character;
    if (color != TRANSPARENT) video_memory[cursor + 1] = color;   // if the color is transparent no will be drawn
		set_cursor_offset(cursor + 2);
  }
}

// print char to cursor with default color
void kprintc(char character)
{
	kprintc_color(character, TRANSPARENT);
}

// print string to cursor with color
void kprints_color(char* text, char color)
{
	while (*text != 0)
	{
		kprintc_color(*text, color);
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

void kdisplay_theme(char color)   // draw a specific color on whole display
{
  INIT_VIDEO
  for (uint i = 1; i < DISPLAY_WIDTH * DISPLAY_WIDTH; i += 2)
  {
    video_memory[i] = color;
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
  for (uint32_t i = 0; i < DISPLAY_WIDTH + DISPLAY_SCROLL_DEBUG; ++i)
  {
    dest_offset[i] = src_offset[i];
    ++i;
  }
}

// scrol display by 1 row up
void kdisplay_scroll()
{
  for (uint row = 1; row < DISPLAY_HEIGHT + 1; ++row) // the +1 overwrites the last row with the next invisble line
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
  // kdisplay_clear();
  kdisplay_scroll();
}

// prints a newline, equivalent to kprintc('\n')
void kprintnl()
{
  uint cursor_offset = get_cursor_offset();
  uint cursor_offset_row = get_offset_row(cursor_offset);
  set_cursor_position( 0, cursor_offset_row + 1);
  if (cursor_offset_row > DISPLAY_HEIGHT + DISPLAY_SCROLL_DETECTION_DEBUG) do_scroll();
}

// clear display by printing a LOT of spaces!
void kdisplay_clear()
{
	for (uint i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; ++i)
	{
		display_char(0, i, 0x00);
	}
	set_cursor_offset(0);
}

void kdisplay_deletec()
{
  set_cursor_offset(get_cursor_offset()-1);
  kprintc(' ');
  set_cursor_offset(get_cursor_offset()-1);
}
