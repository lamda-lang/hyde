#ifndef FILE_H
#define FILE_H

#include "api.h"

File *FileOpen(Char *path, Exception *exception);

Status FileClose(File *file, Exception *exception);

Data *FileRead(File *file, Exception *exception);

Status FileWrite(File *file, Data *data, Exception *exception);

#endif
