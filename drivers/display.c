#include "display.h"


static byte display_theme_current;

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

uint32_t get_cursor_position_x(void)
{
  uint32_t pos = 0;
  port_byte_out(0x3D4, 0x0F);
  pos |= port_byte_in(0x3D5);
  port_byte_out(0x3D4, 0x0E);
  pos |= ((uint32_t)port_byte_in(0x3D5)) << 8;
  return pos % DISPLAY_WIDTH;
}

uint32_t get_cursor_position_y(void)
{
  uint32_t pos = 0;
  port_byte_out(0x3D4, 0x0F);
  pos |= port_byte_in(0x3D5);
  port_byte_out(0x3D4, 0x0E);
  pos |= ((uint32_t)port_byte_in(0x3D5)) << 8;
  return pos / DISPLAY_WIDTH;
}

// draws character at specific offset
void display_char(char character, uint offset, byte color)
{
	INIT_VIDEO
	video_memory[offset*2] = character;
  if (color != 0x00) { video_memory[offset*2 + 1] = color; }
}

// called when display should scroll
void do_scroll()
{
  // kdisplay_clear();
  display_scroll();
}

// prints a newline, equivalent to kprintc('\n')
void printnl()
{
  uint cursor_offset = get_cursor_offset();
  uint cursor_offset_row = get_offset_row(cursor_offset);
  set_cursor_position( 0, cursor_offset_row + 1);
  if (cursor_offset_row > DISPLAY_HEIGHT + DISPLAY_SCROLL_DETECTION_DEBUG) do_scroll();
}

// print char to cursor with color
void kprintc_color(char character, char color)
{
  INIT_VIDEO
	uint cursor = get_cursor_offset();
	if (character == '\n')
	{
		printnl();
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
  kprints_color(text, TRANSPARENT);
}

void display_theme(char color)   // draw a specific color on whole display
{
  INIT_VIDEO
  display_theme_current = color;
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

    dest_offset[i] = src_offset[i];         // scroll text
    dest_offset[i + 1] = src_offset[i + 1]; // scroll color
    ++i;
  }
}

// scrol display by 1 row up
void display_scroll()
{
  for (uint row = 1; row < DISPLAY_HEIGHT + 1; ++row) // the +1 overwrites the last row with the next invisble line
  {
    rowcpy(row - 1, row); // copy the current row to the last (row - 1)
  }
  uint cursor_offset = get_cursor_offset();
  uint cursor_offset_row = get_offset_row(cursor_offset);
  set_cursor_position( 0, cursor_offset_row - 1);
}


// clear display by printing a LOT of spaces!
void display_clear()
{
	for (uint i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; ++i)
	{
		display_char(0, i, 0x00);
	}
	set_cursor_offset(0);
  display_theme(display_theme_current);
}

void display_deletec()
{
  set_cursor_offset(get_cursor_offset()-1);
  kprintc(0);
  set_cursor_offset(get_cursor_offset()-1);
}
