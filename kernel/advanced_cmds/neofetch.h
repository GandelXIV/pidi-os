#pragma once
#include "../../drivers/display.h"

void neofetch()
{
  kprintc('\n');
  kprints("$$$$$$$\\  $$\\\n"
          "$$  __$$\\ \\__|\n"
          "$$ |  $$ |$$\\\n"
          "$$$$$$$  |$$ |\n"
          "$$  ____/ $$ |\n"
          "$$ |      $$ |\n"
          "$$ |      $$ |\n"
          "\\__|      \\__|\n"
          " $$$$$$\\   $$$$$$\\  \n"
          "$$  __$$\\ $$  __$$\\ \n"
          "$$ /  $$ |$$ /  \\__|\n"
          "$$ |  $$ |\\$$$$$$\\  \n"
          "$$ |  $$ | \\____$$\\ \n"
          "$$ |  $$ |$$\\   $$ |\n"
          " $$$$$$  |\\$$$$$$  |\n"
          " \\______/  \\______/ \n");
  set_cursor_position(23, 8);
  kprints("OS: Pidi OS ");
  kprints(OS_VERSION);
  set_cursor_position(23, 9);
  kprints("BIOS name: ");
  kprints(smbios_get_bios_name());
  set_cursor_position(23, 10);
  kprints("BIOS version:");
  kprints(smbios_get_bios_version());
  set_cursor_position(23, 11);
  kprints("Memory: ");
  kprintu32(memory_usage());
  kprints("/");
  kprintu32(memory_total());
  set_cursor_position(23, 12);
  kprints("Theme: ");
  kprints(theme);
  set_cursor_position(0, 24);
  kprintc('\n');
}
/*14 x 28
██████████████████  ████████   moth@moth-pc
██████████████████  ████████   ------------
██████████████████  ████████   OS: Manjaro Linux x86_64
██████████████████  ████████   Host: MS-7788 1.0
████████            ████████   Kernel: 5.10.34-1-MANJARO
████████  ████████  ████████   Uptime: 6 hours, 10 mins
████████  ████████  ████████   Packages: 1388 (pacman), 7 (snap)
████████  ████████  ████████   Shell: bash 5.1.4
████████  ████████  ████████   Resolution: 1920x1080, 1280x1024
████████  ████████  ████████   DE: Plasma 5.21.4
████████  ████████  ████████   WM: KWin
████████  ████████  ████████   WM Theme: Sweet-Mars-transparent
████████  ████████  ████████   Theme: Aritim-Dark_DEV [Plasma], Breeze [GTK2/3]
████████  ████████  ████████ */
