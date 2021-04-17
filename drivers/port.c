#include "../lib/type.h"

byte port_byte_in (word port) {
    byte result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out (word port, byte data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

word port_word_in (word port) {
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out (unsigned short port, word data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
