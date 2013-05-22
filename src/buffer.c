#include "buffer.h"

struct Buffer {
  Byte *bytes;
  Size size;
};

Buffer *BufferCreate(void) {
  Buffer *buffer = MemoryAlloc(sizeof(Buffer));
  if (buffer == NULL) {
    goto error;
  }
  buffer->bytes = NULL;
  buffer->size = 0;
  return buffer;

error:
  return NULL;
}

void BufferDealloc(Buffer *buffer) {
  MemoryDealloc(buffer->bytes);
  MemoryDealloc(buffer);
}

Status BufferAppend(Buffer *buffer, Byte *source, Size size) {
  Byte *bytes = MemoryRealloc(buffer->bytes, buffer->size + size);
  if (bytes == NULL) {
    goto error;
  }
  Byte *target = bytes + buffer->size;
  buffer->bytes = bytes;
  buffer->size += size;
  MemoryCopy(source, target, size);
  return StatusSuccess;

error:
  return StatusFailure;
}

Byte *BufferBytes(Buffer *buffer) {
  return buffer->bytes;
}

Size BufferSize(Buffer *buffer) {
  return buffer->size;
}
