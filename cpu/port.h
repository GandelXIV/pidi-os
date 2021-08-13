#pragma once

#include "../lib/type.h"

byte port_byte_in (word port);
void port_byte_out (word port, byte data);
word port_word_in (word port);
void port_word_out (word port, word data);
