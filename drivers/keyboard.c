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
      case 0x2: return KEY_PRESSED_1;
      case 0x3: return KEY_PRESSED_2;
      case 0x4: return KEY_PRESSED_3;
      case 0x5: return KEY_PRESSED_4;
      case 0x6: return KEY_PRESSED_5;
      case 0x7: return KEY_PRESSED_6;
      case 0x8: return KEY_PRESSED_7;
      case 0x9: return KEY_PRESSED_8;
      case 0xA: return KEY_PRESSED_9;
      case 0xB: return KEY_PRESSED_0;
      case 0xC: return KEY_PRESSED_DASH;
      case 0xD: return KEY_PRESSED_EQUALS;
      case 0xE: return KEY_PRESSED_BACKSPACE;
      case 0xF: return KEY_PRESSED_TAB;
      case 0x10: return KEY_PRESSED_Q;
      case 0x11: return KEY_PRESSED_W;
      case 0x12: return KEY_PRESSED_E;
      case 0x13: return KEY_PRESSED_R;
      case 0x14: return KEY_PRESSED_T;
      case 0x15: return KEY_PRESSED_Y;
      case 0x16: return KEY_PRESSED_U;
      case 0x17: return KEY_PRESSED_I;
      case 0x18: return KEY_PRESSED_O;
      case 0x19: return KEY_PRESSED_P;
      case 0x1A: return KEY_PRESSED_LEFT_SQUARE_BRACKET;
      case 0x1B: return KEY_PRESSED_RIGHT_SQUARE_BRACKET;
      case 0x1C: return KEY_PRESSED_ENTER;
      case 0x1E: return KEY_PRESSED_A;
      case 0x1F: return KEY_PRESSED_S;
      case 0x20: return KEY_PRESSED_D;
      case 0x21: return KEY_PRESSED_F;
      case 0x22: return KEY_PRESSED_G;
      case 0x23: return KEY_PRESSED_H;
      case 0x24: return KEY_PRESSED_J;
      case 0x25: return KEY_PRESSED_K;
      case 0x26: return KEY_PRESSED_L;
      case 0x27: return KEY_PRESSED_SEMICOLON;
      case 0x28: return KEY_PRESSED_BACKSLASH;
      case 0x29: return KEY_PRESSED_BACKTICK;
      case 0x2B: return KEY_PRESSED_BACKSLASH;
      case 0x2C: return KEY_PRESSED_Z;
      case 0x2D: return KEY_PRESSED_X;
      case 0x2E: return KEY_PRESSED_C;
      case 0x2F: return KEY_PRESSED_V;
      case 0x30: return KEY_PRESSED_B;
      case 0x31: return KEY_PRESSED_N;
      case 0x32: return KEY_PRESSED_M;
      case 0x33: return KEY_PRESSED_COMMA;
      case 0x34: return KEY_PRESSED_DOT;
      case 0x35: return KEY_PRESSED_FRONT_SLASH;
      case 0x39: return KEY_PRESSED_SPACE;
      case 0x53: return KEY_PRESSED_DOT;
      /*
      case 0x37: return KEY_PRESSED_'*'; // keypad
      case 0x47: return KEY_PRESSED_'7'; // keypad
      case 0x48: return KEY_PRESSED_'8'; // keypad
      case 0x49: return KEY_PRESSED_'9'; // keypad
      case 0x4A: return KEY_PRESSED_'-'; // keypad
      case 0x4B: return KEY_PRESSED_'4'; // keypad
      case 0x4C: return KEY_PRESSED_'5'; // keypad
      case 0x4D: return KEY_PRESSED_'6'; // keypad
      case 0x4E: return KEY_PRESSED_'+'; // keypad
      case 0x4F: return KEY_PRESSED_'1'; // keypad
      case 0x50: return KEY_PRESSED_'2'; // keypad
      case 0x51: return KEY_PRESSED_'3'; // keypad
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
      case KEY_PRESSED_1: return '1';
      case KEY_PRESSED_2: return '2';
      case KEY_PRESSED_3: return '3';
      case KEY_PRESSED_4: return '4';
      case KEY_PRESSED_5: return '5';
      case KEY_PRESSED_6: return '6';
      case KEY_PRESSED_7: return '7';
      case KEY_PRESSED_8: return '8';
      case KEY_PRESSED_9: return '9';
      case KEY_PRESSED_0: return '0';
      case KEY_PRESSED_DASH: return '-';
      case KEY_PRESSED_EQUALS: return '=';
      case KEY_PRESSED_BACKSPACE: return '\b';
      case KEY_PRESSED_TAB: return '\t';
      case KEY_PRESSED_Q: return 'q';
      case KEY_PRESSED_W: return 'w';
      case KEY_PRESSED_E: return 'e';
      case KEY_PRESSED_R: return 'r';
      case KEY_PRESSED_T: return 't';
      case KEY_PRESSED_Y: return 'y';
      case KEY_PRESSED_U: return 'u';
      case KEY_PRESSED_I: return 'i';
      case KEY_PRESSED_O: return 'o';
      case KEY_PRESSED_P: return 'p';
      case KEY_PRESSED_LEFT_SQUARE_BRACKET: return '[';
      case KEY_PRESSED_RIGHT_SQUARE_BRACKET: return ']';
      case KEY_PRESSED_ENTER: return '\n';
      case KEY_PRESSED_A: return 'a';
      case KEY_PRESSED_S: return 's';
      case KEY_PRESSED_D: return 'd';
      case KEY_PRESSED_F: return 'f';
      case KEY_PRESSED_G: return 'g';
      case KEY_PRESSED_H: return 'h';
      case KEY_PRESSED_J: return 'j';
      case KEY_PRESSED_K: return 'k';
      case KEY_PRESSED_L: return 'l';
      case KEY_PRESSED_SEMICOLON: return ';';
      case KEY_PRESSED_APOSTROPHE: return '\'';
      case KEY_PRESSED_BACKTICK: return '`';
      case KEY_PRESSED_BACKSLASH: return '\\';
      case KEY_PRESSED_Z: return 'z';
      case KEY_PRESSED_X: return 'x';
      case KEY_PRESSED_C: return 'c';
      case KEY_PRESSED_V: return 'v';
      case KEY_PRESSED_B: return 'b';
      case KEY_PRESSED_N: return 'n';
      case KEY_PRESSED_M: return 'm';
      case KEY_PRESSED_COMMA: return ',';
      case KEY_PRESSED_DOT: return '.';
      case KEY_PRESSED_FRONT_SLASH: return '/';
      case KEY_PRESSED_SPACE: return ' ';
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
