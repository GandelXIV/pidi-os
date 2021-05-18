typedef unsigned long uint32_t;
typedef unsigned char byte;
typedef unsigned char* bytes;
typedef unsigned int uint;
typedef unsigned short word;
typedef unsigned char bool;
#define true (bool) 1
#define false (bool) 0

#define low_16(address) (word)((address) & 0xFFFF)
#define high_16(address) (word)(((address) >> 16) & 0xFFFF)
