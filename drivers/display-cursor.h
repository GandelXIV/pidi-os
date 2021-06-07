#include "../firmware/port.h"

#define REG_DISPLAY_CTRL 0x3d4
#define REG_DISPLAY_DATA 0x3d5

uint32_t get_cursor_position_x(void);
uint32_t get_cursor_position_y(void);
uint get_cursor_offset();
void set_cursor_offset(uint offset);
