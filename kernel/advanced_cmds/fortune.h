#pragma once
#include "../../drivers/display.h"

void ksh_fortune() {
  const char fortunes[3] = {"Pohl's Law: Nothing is so good that somebody, somewhere, will not hate it.", "You either die a smart fella, or live long enough to become a fart smella", "Everyone asked you about your favorite dinosaur as a kid, now, nobody cares"};
  kprintc("\n");
  int RandIndex = rand() % 3;
  kprintc(arrayNum[RandIndex]);
  kprintc("\n");
}
