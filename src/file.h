#ifndef FILE_H
#define FILE_H

#include "api.h"

File *FileCreateStandardInput(Error *error);
void FileDealloc(File *file);
File *FileOpen(Char *path, Error *error);
Status FileClose(File *file, Error *error);
Status FileRead(File *file, Data *data, Error *error);
Status FileWrite(File *file, Data *data, Error *error);

#endif
