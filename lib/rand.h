#include "type.h"

#define LCG_A 1103515245
#define LCG_C 12345
#define LCG_M 2147483648

void rand_init();
int rand_lcg(int x);
int rand();
