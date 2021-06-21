#include "rand.h"

int rand_seed;

void rand_init()
{
  int random_data;  // we allocate data and dont initalize it
  rand_seed = random_data + 2;  // +1 to make sure there is not a zero
}

// Linear congruential generator function
// more info: https://en.wikipedia.org/wiki/Linear_congruential_generator
int rand_lcg(int x)
{
  // we use the same parameters as glibc https://en.wikipedia.org/wiki/Linear_congruential_generator#Parameters_in_common_use
  int a = 1103515245;
  int c = 12345;
  int m = 2147483648;
  int result = (a * x + c) % m;
  if (result < 0) result = -result;
  return result;
}

int rand()
{
  rand_seed = rand_lcg(rand_seed);  // randomize the seed
  return rand_seed;
}
