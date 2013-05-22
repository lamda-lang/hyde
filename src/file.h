#ifndef FILE_H
#define FILE_H

#include "runtime.h"

Status FileRead(File file, Buffer *buffer);

Status FileWrite(File file, Buffer *buffer);

#endif
