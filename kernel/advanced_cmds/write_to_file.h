void ksh_write_to_file()
{
  kprints("Enter file name: ");
  char* filename = (char*) kmalloc(256);
  strcls(filename);
  kinputs(filename);

  char* data = (char*) kmalloc(256);
  strcls(data);
  kprints("Enter data: ");
  kinputs(data);
  stradd(data, "\n");

  file_clean(filename);
  int response = file_writes(filename, data);
  if (response == FILE_NOT_FOUND)
  {
    kprints("File not found!\n");
  }

  kfree(filename);
  kfree(data);
}
