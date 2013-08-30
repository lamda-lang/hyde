#ifndef FILE_H
#define FILE_H

#include "runtime.h"

File FileOpen(Char *path, Error *error);
void FileClose(File file, Error *error);
Size FileRead(File file, void *buffer, Size size, Error *error);
Size FileWrite(File file, void *buffer, Size size, Error *error);

#endif
