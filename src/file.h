#ifndef FILE_H
#define FILE_H

#include "runtime.h"

File FileOpen(Char *path, VALUE **error);
void FileClose(File file, VALUE **error);
Size FileRead(File file, void *buffer, Size size, VALUE **error);
Size FileWrite(File file, void *buffer, Size size, VALUE **error);

#endif
