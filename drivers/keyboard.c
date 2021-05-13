#include "../lib/type.h"
#include "keyboard.h"
#include "display.h"
#include "../firmware/port.h"
#include "../firmware/isr.h"

KeyEvent keyboard_old_event;
byte scan_code_set;

KeyEvent scan_code_to_key_event(byte code)
{
  if (scan_code_set == 0x1)
  {
    switch (code) {
      case 0x2: return KEY_DOWN_1;
      case 0x3: return KEY_DOWN_2;
      case 0x4: return KEY_DOWN_3;
      case 0x5: return KEY_DOWN_4;
      case 0x6: return KEY_DOWN_5;
      case 0x7: return KEY_DOWN_6;
      case 0x8: return KEY_DOWN_7;
      case 0x9: return KEY_DOWN_8;
      case 0xA: return KEY_DOWN_9;
      case 0xB: return KEY_DOWN_0;
      case 0xC: return KEY_DOWN_DASH;
      case 0xD: return KEY_DOWN_EQUALS;
      case 0xE: return KEY_DOWN_BACKSPACE;
      case 0xF: return KEY_DOWN_TAB;
      case 0x10: return KEY_DOWN_Q;
      case 0x11: return KEY_DOWN_W;
      case 0x12: return KEY_DOWN_E;
      case 0x13: return KEY_DOWN_R;
      case 0x14: return KEY_DOWN_T;
      case 0x15: return KEY_DOWN_Y;
      case 0x16: return KEY_DOWN_U;
      case 0x17: return KEY_DOWN_I;
      case 0x18: return KEY_DOWN_O;
      case 0x19: return KEY_DOWN_P;
      case 0x1A: return KEY_DOWN_LEFT_SQUARE_BRACKET;
      case 0x1B: return KEY_DOWN_RIGHT_SQUARE_BRACKET;
      case 0x1C: return KEY_DOWN_ENTER;
      case 0x1E: return KEY_DOWN_A;
      case 0x1F: return KEY_DOWN_S;
      case 0x20: return KEY_DOWN_D;
      case 0x21: return KEY_DOWN_F;
      case 0x22: return KEY_DOWN_G;
      case 0x23: return KEY_DOWN_H;
      case 0x24: return KEY_DOWN_J;
      case 0x25: return KEY_DOWN_K;
      case 0x26: return KEY_DOWN_L;
      case 0x27: return KEY_DOWN_SEMICOLON;
      case 0x28: return KEY_DOWN_BACKSLASH;
      case 0x29: return KEY_DOWN_BACKTICK;
      case 0x2B: return KEY_DOWN_BACKSLASH;
      case 0x2C: return KEY_DOWN_Z;
      case 0x2D: return KEY_DOWN_X;
      case 0x2E: return KEY_DOWN_C;
      case 0x2F: return KEY_DOWN_V;
      case 0x30: return KEY_DOWN_B;
      case 0x31: return KEY_DOWN_N;
      case 0x32: return KEY_DOWN_M;
      case 0x33: return KEY_DOWN_COMMA;
      case 0x34: return KEY_DOWN_DOT;
      case 0x35: return KEY_DOWN_FRONT_SLASH;
      case 0x39: return KEY_DOWN_SPACE;
      case 0x53: return KEY_DOWN_DOT;
      /*
      case 0x37: return KEY_DOWN_'*'; // keypad
      case 0x47: return KEY_DOWN_'7'; // keypad
      case 0x48: return KEY_DOWN_'8'; // keypad
      case 0x49: return KEY_DOWN_'9'; // keypad
      case 0x4A: return KEY_DOWN_'-'; // keypad
      case 0x4B: return KEY_DOWN_'4'; // keypad
      case 0x4C: return KEY_DOWN_'5'; // keypad
      case 0x4D: return KEY_DOWN_'6'; // keypad
      case 0x4E: return KEY_DOWN_'+'; // keypad
      case 0x4F: return KEY_DOWN_'1'; // keypad
      case 0x50: return KEY_DOWN_'2'; // keypad
      case 0x51: return KEY_DOWN_'3'; // keypad
      case 0x52: return '0'; // keypad
      */
      default: return KEY_VOID;  // no printable character
    }
  }
}

byte read_keyboard_stream()
{
  return port_byte_in(REG_KEYBOARD_DATA);
}

KeyEvent keyboard_get()
{
  KeyEvent event = scan_code_to_key_event(read_keyboard_stream());
  if (event == keyboard_old_event) return KEY_VOID;
  keyboard_old_event = event;
  return event;
}

void on_key_event(registers_t registers)
{
  kprints("Registered event!");
}

void keyboard_init()
{
  scan_code_set = 0x1;
  register_interrupt_handler(IRQ1, on_key_event);
}

char key_event_to_char(KeyEvent code)
{
  if (scan_code_set == 0x1)
  {
    switch (code) {
      case KEY_DOWN_1: return '1';
      case KEY_DOWN_2: return '2';
      case KEY_DOWN_3: return '3';
      case KEY_DOWN_4: return '4';
      case KEY_DOWN_5: return '5';
      case KEY_DOWN_6: return '6';
      case KEY_DOWN_7: return '7';
      case KEY_DOWN_8: return '8';
      case KEY_DOWN_9: return '9';
      case KEY_DOWN_0: return '0';
      case KEY_DOWN_DASH: return '-';
      case KEY_DOWN_EQUALS: return '=';
      case KEY_DOWN_BACKSPACE: return '\b';
      case KEY_DOWN_TAB: return '\t';
      case KEY_DOWN_Q: return 'q';
      case KEY_DOWN_W: return 'w';
      case KEY_DOWN_E: return 'e';
      case KEY_DOWN_R: return 'r';
      case KEY_DOWN_T: return 't';
      case KEY_DOWN_Y: return 'y';
      case KEY_DOWN_U: return 'u';
      case KEY_DOWN_I: return 'i';
      case KEY_DOWN_O: return 'o';
      case KEY_DOWN_P: return 'p';
      case KEY_DOWN_LEFT_SQUARE_BRACKET: return '[';
      case KEY_DOWN_RIGHT_SQUARE_BRACKET: return ']';
      case KEY_DOWN_ENTER: return '\n';
      case KEY_DOWN_A: return 'a';
      case KEY_DOWN_S: return 's';
      case KEY_DOWN_D: return 'd';
      case KEY_DOWN_F: return 'f';
      case KEY_DOWN_G: return 'g';
      case KEY_DOWN_H: return 'h';
      case KEY_DOWN_J: return 'j';
      case KEY_DOWN_K: return 'k';
      case KEY_DOWN_L: return 'l';
      case KEY_DOWN_SEMICOLON: return ';';
      case KEY_DOWN_APOSTROPHE: return '\'';
      case KEY_DOWN_BACKTICK: return '`';
      case KEY_DOWN_BACKSLASH: return '\\';
      case KEY_DOWN_Z: return 'z';
      case KEY_DOWN_X: return 'x';
      case KEY_DOWN_C: return 'c';
      case KEY_DOWN_V: return 'v';
      case KEY_DOWN_B: return 'b';
      case KEY_DOWN_N: return 'n';
      case KEY_DOWN_M: return 'm';
      case KEY_DOWN_COMMA: return ',';
      case KEY_DOWN_DOT: return '.';
      case KEY_DOWN_FRONT_SLASH: return '/';
      case KEY_DOWN_SPACE: return ' ';
      default: return UNPRINTALBE_CHAR;  // no printable character
    }
  }
}

char kinputc()
{
  KeyEvent event = KEY_VOID;
  char output = UNPRINTALBE_CHAR;

  while (output == UNPRINTALBE_CHAR)
  {
    // wait for new keyboard event
    while (event == KEY_VOID)
    {
      event = keyboard_get();
    }
    // translate event to char
    output = key_event_to_char(event);
  }
  return output;
}
