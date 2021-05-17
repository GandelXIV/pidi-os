void neofetch () {
  char *mem = (unsigned char *) 0xF0000;
  int length, i;
  unsigned char checksum;
  while ((unsigned int) mem < 0x100000) {
      if (mem[0] == '_' && mem[1] == 'S' && mem[2] == 'M' && mem[3] == '_') {
          length = mem[5];
          checksum = 0;
          for(i = 0; i < length; i++) {
              checksum += mem[i];
          }
          if(checksum == 0) break;
      }
      mem += 16;
  }
  if ((unsigned int) mem == 0x100000) {
    kprints("No SMBIOS found!");
  }
}
