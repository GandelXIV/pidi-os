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
      case 0x2: return '1';
      case 0x3: return '2';
      case 0x4: return '3';
      case 0x5: return '4';
      case 0x6: return '5';
      case 0x7: return '6';
      case 0x8: return '7';
      case 0x9: return '8';
      case 0xA: return '9';
      case 0xB: return '0';
      case 0xC: return '-';
      case 0xD: return '=';
      case 0xE: return '\b';
      case 0xF: return '\t';
      case 0x10: return 'q';
      case 0x11: return 'w';
      case 0x12: return 'e';
      case 0x13: return 'r';
      case 0x14: return 't';
      case 0x15: return 'y';
      case 0x16: return 'u';
      case 0x17: return 'i';
      case 0x18: return 'o';
      case 0x19: return 'p';
      case 0x1A: return '[';
      case 0x1B: return ']';
      case 0x1C: return '\n';
      case 0x1E: return 'a';
      case 0x1F: return 's';
      case 0x20: return 'd';
      case 0x21: return 'f';
      case 0x22: return 'g';
      case 0x23: return 'h';
      case 0x24: return 'j';
      case 0x25: return 'k';
      case 0x26: return 'l';
      case 0x27: return ';';
      case 0x28: return '\'';
      case 0x29: return '`';
      case 0x2B: return '\\';
      case 0x2C: return 'z';
      case 0x2D: return 'x';
      case 0x2E: return 'c';
      case 0x2F: return 'v';
      case 0x30: return 'b';
      case 0x31: return 'n';
      case 0x32: return 'm';
      case 0x33: return ',';
      case 0x34: return '.';
      case 0x35: return '/';
      case 0x37: return '*'; // keypad
      case 0x39: return ' ';
      case 0x47: return '7'; // keypad
      case 0x48: return '8'; // keypad
      case 0x49: return '9'; // keypad
      case 0x4A: return '-'; // keypad
      case 0x4B: return '4'; // keypad
      case 0x4C: return '5'; // keypad
      case 0x4D: return '6'; // keypad
      case 0x4E: return '+'; // keypad
      case 0x4F: return '1'; // keypad
      case 0x50: return '2'; // keypad
      case 0x51: return '3'; // keypad
      case 0x52: return '0'; // keypad
      case 0x53: return '.';
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
