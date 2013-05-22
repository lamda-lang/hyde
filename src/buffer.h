#ifndef BUFFER_H
#define BUFFER_H

#include "runtime.h"

Buffer *BufferCreate(void);

void BufferDealloc(Buffer *buffer);

Status BufferAppend(Buffer *buffer, Byte *source, Size size);

Byte *BufferBytes(Buffer *buffer);

Size BufferSize(Buffer *buffer);

#endif
