void ksh_remove_file()
{
  kprints("Enter file name: ");
  char file_to_remove [255];
  kinputs(file_to_remove);
  if (file_remove(file_to_remove) == FILE_NOT_FOUND)
  {
    kprints("File not found!\n");
  }
}
