#pragma once
#include "../io.h"
#include "../../lib/rand.h"
#include "../../drivers/display.h"

void ksh_fortune() {
  const char fortunes[3] = {"Pohl's Law: Nothing is so good that somebody, somewhere, will not hate it.", "You either die a smart fella, or live long enough to become a fart smella", "Everyone asked you about your favorite dinosaur as a kid, now, nobody cares", "Even stock traders want to arrest hatred", "Generically, fiery liquors that produce madness in total abstainers.", "Our remedies oft in ourselves do lie,? Which we ascribe to heaven.", "One of the most conspicuous qualities of a man in security."};
  kprintc('\n');
  int RandIndex = rand() % sizeof(fortunes);
  kprints(arrayNum[RandIndex]);
  kprintc('\n');
}
