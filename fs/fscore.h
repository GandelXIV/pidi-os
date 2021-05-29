#pragma once

// includes
#include "prop.h"
#include "../lib/type.h"
#include "../lib/string.h"
#include "../kernel/config.h"
#include "../kernel/mem.h"
#include "../kernel/kmsg.h"

// defines
#define OK 0
#define FILE_COUNT_MAX_EXCEEDED 1
#define FILE_ALREADY_EXISTS 2
#define FILE_NOT_FOUND 1

// declarations
void fsinit();
int file_remove(char* name);
int file_make(char* name);
char* file_get_name(int id);
int file_get_id(char* name);
int file_count();
bool file_exists(char* name);
int file_size(char* name);
int file_read(char* output, char* filename);
