#define REG_KEYBOARD_DATA 0x60
#define REG_KEYBOARD_CTRL 0x64
#define KEYBOARD_NO_PRINTABLE_CHARACTER 0x0

typedef enum
{
  KEY_PRESSED_BACKTICK,
  KEY_PRESSED_DASH,
  KEY_PRESSED_EQUALS,
  KEY_PRESSED_BACKSPACE,
  KEY_PRESSED_1,
  KEY_PRESSED_2,
  KEY_PRESSED_3,
  KEY_PRESSED_4,
  KEY_PRESSED_5,
  KEY_PRESSED_6,
  KEY_PRESSED_7,
  KEY_PRESSED_8,
  KEY_PRESSED_9,
  KEY_PRESSED_0,
  KEY_PRESSED_Q,
  KEY_PRESSED_W,
  KEY_PRESSED_E,
  KEY_PRESSED_R,
  KEY_PRESSED_T,
  KEY_PRESSED_Y,
  KEY_PRESSED_U,
  KEY_PRESSED_I,
  KEY_PRESSED_O,
  KEY_PRESSED_P,
  KEY_PRESSED_TAB,
  KEY_PRESSED_A,
  KEY_PRESEED_S,
  KEY_PRESEED_D,
  KEY_PRESEED_F,
  KEY_PRESEED_G,
  KEY_PRESEED_H,
  KEY_PRESEED_J,
  KEY_PRESEED_K,
  KEY_PRESEED_SEMICOLON,
  KEY_PRESEED_APOSTROPHE,
  KEY_PRESEED_BACKSLASH,
  KEY_PRESEED_LEFT_SHIFT,
  KEY_PRESEED_SMALLER,
  KEY_PRESEED_Z,
  KEY_PRESEED_X,
  KEY_PRESEED_C,
  KEY_PRESEED_V,
  KEY_PRESEED_B,
  KEY_PRESEED_N,
  KEY_PRESEED_M,
  KEY_PRESEED_COMMA,
  KEY_PRESEED_DOT,
  KEY_PRESEED_FRONT_SLASH,
  KEY_PRESEED_RIGHT_SHIFT,
  KEY_PRESEED_LEFT_CTRL,
  KEY_PRESEED_LEFT_SUPER,
  KEY_PRESEED_LEFT_ALT,
  KEY_PRESEED_SPACE,
  KEY_PRESEED_RIGHT_ALT,
  KEY_PRESEED_RIGHT_SUPER,
  KEY_PRESEED_FM,
  KEY_PRESEED_RIGHT_CTRL,
  // more keys
} KeyEvent;

char kinputc();
void keyboard_init();
