#include "fscore.h"

#define FS_SECTOR_DATA_SIZE FS_SECTOR_SIZE - sizeof(struct Sector*)

#define END_SECTOR 0

struct SectorStruct
{
  struct Sector* next;
  byte data[FS_SECTOR_DATA_SIZE];
};
typedef struct SectorStruct Sector;

typedef struct
{
  char name [FS_FILE_NAME_BUFFER];
  char tags [FS_FILE_TAGS_BUFFER];
  Sector* first_sector;
} File;

File* findex [sizeof(File*) * FS_MAX_FILE_COUNT];
int findex_end = 0;

File* find_file(char* name)
{
  for (int i = 0; i <= findex_end; ++i)
  {
    if (strcmp(findex[i]->name, name))
    {
      return findex[i];
    }
  }
}

bool file_exists(char* name)
{
  for (int i = 0; i <= findex_end; ++i)
  {
    if (strcmp(findex[i]->name, name))
    {
      return true;
    }
  }
  return false;
}

int file_count()
{
  return findex_end;
}

char* file_get_name(int id)
{
  return findex[id]->name;
}

int file_get_id(char* name)
{
  for (int i = 0; i < findex_end; ++i)
  {
    if (strcmp(findex[i]->name, name))
    {
      return i;
    }
  }
}

// create new file
int file_make(char* name)
{
  if (findex_end >= FS_MAX_FILE_COUNT)
  {
    return FILE_COUNT_MAX_EXCEEDED;
  }
  if (file_exists(name))
  {
    return FILE_ALREADY_EXISTS;
  }
  // allocate the file
  File* fp = kmalloc(sizeof(File));
  strcpy(fp->name, name);
  // prepare the sector
  Sector* fs = kmalloc(sizeof(Sector));
  fp->first_sector = fs;
  fs->next = END_SECTOR;
  for (int i = 0; i < FS_SECTOR_DATA_SIZE; ++i)  // delete potentional data in the sector
  {
    fs->data[i] = 0;
  }
  // asign the file
  findex[findex_end] = fp;
  findex_end += 1;
  return OK;
}

// delete file
int file_remove(char* name)
{
  for (int i = 0; i < findex_end; ++i)
  {
    if (strcmp(findex[i]->name, name))
    {
      findex[i] = 0;
      findex_end -= 1;
      return OK;
    }
  }
  return FILE_NOT_FOUND;
}

int file_size(char* name)
{
  File* fp = find_file(name);
  Sector* fs = fp->first_sector;
  // find the size
  int size = sizeof(fs->data);
  while (fs->next != END_SECTOR)
  {
    fs = fs->next;   // jump to next sector
    size += sizeof(fs->data);
  }
  return size;
}

// write content of file to $output
int file_read(char* output, char* filename)
{
  if (!file_exists(filename))
  {
    return FILE_NOT_FOUND;
  }
  File* fp = find_file(filename);
  Sector* fs = fp->first_sector;
  do {
    for (int i = 0; i < FS_SECTOR_DATA_SIZE; ++i)
    {
      output[i] = fs->data[i];
    }
    output += FS_SECTOR_DATA_SIZE;
    fs = fs->next;
  } while(fs->next != 0);
  return OK;
}


void fsinit()
{
  file_make("test-file.info");
  file_make("another-file.stat");
  /*
  char* output = kmalloc(file_size("test-file.info"));
  file_read(output, "test-file.info");
  kprints(output);
  */
}
