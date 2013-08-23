#ifndef FILE_H
#define FILE_H

#include "api.h"

File FileOpen(Char *path, Value **error);
void FileClose(File file, Value **error);
Size FileRead(File file, void *buffer, Size count, Value **error);
Size FileWrite(File file, void *buffer, Size count, Value **error);

#endif
