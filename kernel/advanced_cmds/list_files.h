#pragma once

#include "../../fs/fscore.h"

void list_files()
{
  for (int i = 0; i < file_count(); ++i)
  {
    kprints(file_get(i));
    kprintc('\n');
  }
}
