void ksh_read_file()
{
  // get the filename
  char* filename = (char*) kmalloc(256);
  kprints("Enter file name: ");
  kinputs(filename);
  // read it
  char* content = (char*) kmalloc(file_size(filename));
  int response = file_read(filename, content);
  if (response == FILE_NOT_FOUND)
  {
    kprints("File not found\n");
  }
  kprints(content);
  // cleanup
  kfree(filename);
  kfree(content);
}
