#ifndef FILE_H
#define FILE_H

#include "api.h"

File *FileOpen(Char *path, Error *error);

Status FileClose(File *file, Error *error);

Data *FileRead(File *file, Error *error);

Status FileWrite(File *file, Data *data, Error *error);

#endif