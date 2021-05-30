void ksh_read_file()
{
  // get the filename
  char* filename = (char*) kmalloc(256);
  kprints("Enter file name: ");
  kinputs(filename);
  // read it
  char* content = (char*) kmalloc(file_size(filename));
  file_read(filename, content);
  kprints(content);
  // cleanup
  kfree(filename);
  kfree(content);
}
