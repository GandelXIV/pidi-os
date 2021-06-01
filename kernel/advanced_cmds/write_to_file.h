void ksh_write_to_file()
{
  kprints("Enter file name: ");
  char* filename = (char*) kmalloc(256);
  kinputs(filename);

  char* data = (char*) kmalloc(256);
  kprints("Enter data: ");
  kinputs(data);
  stradd(data, "\n");

  file_clean(filename);
  file_writes(filename, data);

  kfree(filename);
  kfree(data);
}
