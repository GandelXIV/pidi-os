void ksh_make_file()
{
  kprints("Enter file name: ");
  char* file_to_make = kmalloc(512);
  kinputs(file_to_make);
  int response = file_make(file_to_make);
  if (response == FILE_ALREADY_EXISTS)
  {
    kprints("File already exists!\n");
  }
  else if (response == FILE_NAME_INVALID)
  {
    kprints("File name can only contain the following characters:\n");
    kprints(FS_FILE_NAME_VALID_CHARS);
    kprintc('\n');
  }
  else if (response == FILE_COUNT_MAX_EXCEEDED)
  {
    kprints("There are too many files!\n");
  }
  kfree(file_to_make);
}
