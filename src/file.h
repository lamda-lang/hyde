#ifndef FILE_H
#define FILE_H

#include "api.h"

Status FileRead(File file, Buffer *buffer);

Status FileWrite(File file, Buffer *buffer);

#endif
