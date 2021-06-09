#include "keyboard.h"
#include <stddef.h>

//TODO: Fix interrupts pls so I can un-bruh this code

bool keydown[384];

static unsigned char keymap_lower[128] =
"\e1234567890-=\b\tqwertyuiop[]\n\0asdfghjkl;'`\0\\zxcvbnm,./\0*\0 \0\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\0\0""789-456+1230.\0\0\0\x8A\x8B";

static unsigned char keymap_upper[128] =
"\e!@#$%^&*()_+\b\tQWERTYUIOP{}\n\0ASDFGHJKL:\"~\0|ZXCVBNM<>?\0*\0 \0\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\0\0""789-456+1230.\0\0\0\x8A\x8B";

static unsigned char keymap_special[128] =
"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\n\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0/\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x90\x8C\x92\0\x8D\0\x8E\0\x91\x8F\x93\x94\x7F\0\0\0\0\0\0\0\x95\x96";

static unsigned char keymap_ascii[128] =
"\e1234567890-=\b\t\x11\x17\x05\x12\x14\x19\x15\x09\x0F\x10[]\r\0\x01\x13\x04\x06\x07\x08\x0A\x0B\x0C;'`\0\\\x1A\x18\x03\x16\x02\x0E\x0D,./\0*\0 \0\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\0""789-456+1230.\0\0\0\x8A\x8B";

bool c_lock = false, n_lock = false, s_lock = false;
bool lsft_d = false, lctl_d = false, lalt_d = false;
bool rsft_d = false, rctl_d = false, ralt_d = false;

bool kb_alt_char = false;

unsigned int kbin;
static bool key = false;

static unsigned char c = 0;

bool xE0 = false;

int tmpptr = 0;
unsigned char tmpbuf[4] = "\0\0\0";

void kbh();

static unsigned char ch = 0;

char kinputc() {
    do {
        if (kbin >= 128 || kbin == 0xE0) ch = 0;
        kbh();
    } while (c == ch || kbin >= 128);
    ch = c;
    return (char)ch;
}

byte scan_code_set;

//#include <util.c>
int atoi(char* str) {
    int res = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        res = res * 10 + str[i] - '0';
    }
    return res;
}

void kbport_byte_out(unsigned char byte) {
    unsigned char tmp;
    int tries = 0;
    do {
        port_byte_out(0x60, byte);
        do {
            tmp = port_byte_in(0x60);
            //kprintf("0x%_x (0x%_x): 0x%_x\n", port, 4, byte, 2, tmp, 2);
        } while (tmp == 0);
        tries++;
    } while (tmp == 0xFE && tries < 3);
}    

void kbupdateleds() {
    kbport_byte_out(0xED);
    kbport_byte_out((s_lock & 1) + ((n_lock & 1) << 1) + ((c_lock & 1) << 2));
}

void kbh() {
    kbin = port_byte_in(0x60);
    //kprintf("Keyboard: 0x%_x [%d][%d|%d|%d][%d|%d|%d][%d|%d|%d] ", kbin, 2, xE0, c_lock, n_lock, s_lock, lsft_d, lctl_d, lalt_d, rsft_d, rctl_d, ralt_d);
    kb_alt_char = false;
    c = 0;
    if (kbin == 0xE0) {
        xE0 = true;
        goto kbend;
    }
    if (kbin < 128) {
        if (!n_lock && kbin >= 0x47 && kbin <= 0x52) xE0 = true;
        if (xE0) {
            switch (kbin) {
                case 0x1D:
                    rctl_d = true;
                    break;
                case 0x38:
                    ralt_d = true;
                    break;
                default:
                    c = keymap_special[kbin - 1];
                    keydown[kbin + 127] = true;
                    break;
            }
            xE0 = false;
        } else {
            switch (kbin) {
                case 0x1D:
                    lctl_d = true;
                    break;
                case 0x2A:
                    lsft_d = true;
                    break;
                case 0x36:
                    rsft_d = true;
                    break;
                case 0x38:
                    lalt_d = true;
                    break;
                case 0x3A:
                    c_lock = !c_lock;
                    kbupdateleds();
                    break;
                case 0x45:
                    n_lock = !n_lock;
                    kbupdateleds();
                    break;
                case 0x46:
                    s_lock = !s_lock;
                    kbupdateleds();
                    break;
                default:
                    if (lalt_d || ralt_d) {
                        if (keymap_lower[kbin - 1] >= '0' && keymap_lower[kbin - 1] <= '9' && tmpptr < 3 && kbin >= 0x47 && kbin <= 0x52) {
                            tmpbuf[tmpptr] = keymap_lower[kbin - 1];
                            tmpptr++;
                        }
                    } else {
                        if (lctl_d || rctl_d) {
                            c = keymap_ascii[kbin - 1];
                        } else {
                            if (c_lock) {
                                if (lsft_d || rsft_d) {
                                    c = keymap_lower[kbin - 1];
                                } else {
                                    c = keymap_upper[kbin - 1];
                                }
                            } else {
                                if (lsft_d || rsft_d) {
                                    c = keymap_upper[kbin - 1];
                                } else {
                                    c = keymap_lower[kbin - 1];
                                }
                            }
                        }
                        keydown[kbin - 1] = true;
                    }
                    break;
            }
        }
    } else {
        kbin -= 128;
        if (!n_lock && kbin >= 0x47 && kbin <= 0x52) xE0 = true;
        if (xE0) {
            switch (kbin) {
                case 0x1D:
                    rctl_d = false;
                    break;
                case 0x38:
                    ralt_d = false;
                    break;
                default:
                    keydown[kbin + 127] = false;
                    break;
            }
            xE0 = false;
        } else {
            switch (kbin) {
                case 0x1D:
                    lctl_d = false;
                    break;
                case 0x2A:
                    lsft_d = false;
                    break;
                case 0x36:
                    rsft_d = false;
                    break;
                case 0x38:
                    lalt_d = false;
                    break;
                case 0x3A:
                    break;
                case 0x45:
                    break;
                case 0x46:
                    break;
                default:
                    keydown[kbin - 1] = false;
                    break;
            }
            kbin += 128;
        }
        if (!(lalt_d || ralt_d) && tmpptr > 0) {
            //kprintf("[%d] {", tmpptr);
            c = atoi(tmpbuf) % 256;
            //kprintf("%s} (%d) [%d] ", tmpbuf, c, tmpptr);
            for (tmpptr = 0; tmpptr < 3; tmpptr++) {
                tmpbuf[tmpptr] = 0;
            }
            tmpptr = 0;
            kb_alt_char = true;
        }
    }
    kbend:
    //kputchar(c);
    //kputchar('\n');
    //if ((lctl_d || rctl_d) && (lalt_d || ralt_d) && c == 127) reboot();
    //if (xE0 && kbin == 0x5E) reboot();
    key = true;
}

void on_key_event(registers_t registers)
{
    //kprints("Registered event!");
}

void keyboard_init() {
    key = false;
    for (int i = 0; i < 384; i++) {keydown[i] = false;}
    n_lock = true;
    kbupdateleds();
    register_interrupt_handler(IRQ1, kbh);
}
