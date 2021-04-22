/*
NOTE: This driver does not use interrupt!
*/

#include "../lib/type.h"
#include "keyboard.h"
#include "port.h"

byte old_scan_code;
byte scan_code_set;

byte read_keyboard_stream()
{
  return port_byte_in(KEYBOARD_PORT);
}

byte get_new_scan_code()
{
  while ( read_keyboard_stream() == old_scan_code) {}
  old_scan_code = read_keyboard_stream();
  return old_scan_code;
}

void kkeyboard_init()
{
  scan_code_set = 0x1;
}

char scan_code_to_char(byte code)
{
  if (scan_code_set == 0x1)
  {
    switch (code) {
      case 0x1C: return '\n';
      case 0x1E: return 'a';
      case 0x02: return '1';
      case 0x03: return '2';
      case 0x04: return '3';
      case 0x05: return '4';
      case 0x06: return '5';
      case 0x07: return '6';
      case 0x08: return '7';
      case 0x09: return '8';
      case 0x0A: return '9';
      case 0x0B: return '0';
      case 0x0C: return '-';
      case 0x0D: return '=';
      case 0x0E: return '\b';
      default: return 0x0;  // no printable character
    }
  }
}

char kinputc()
{
  char output = 0x0;
  while (output == 0x0)
  {
    output = scan_code_to_char( (char) get_new_scan_code());
  }
  return output;
}
