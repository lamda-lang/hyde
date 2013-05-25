#ifndef FILE_H
#define FILE_H

#include "api.h"

File *FileOpen(Char *path);

Status FileClose(File *file);

Data *FileRead(File *file);

Status FileWrite(File *file, Data *data);

#endif
