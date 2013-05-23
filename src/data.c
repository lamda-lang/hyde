#include "data.h"

struct Data {
  Byte *bytes;
  Size size;
};

Data *DataCreate(void) {
  Data *buffer = MemoryAlloc(sizeof(Data));
  if (buffer == NULL) {
    goto error;
  }
  buffer->bytes = NULL;
  buffer->size = 0;
  return buffer;

error:
  return NULL;
}

void DataDealloc(Data *buffer) {
  MemoryDealloc(buffer->bytes);
  MemoryDealloc(buffer);
}

Status DataAppend(Data *buffer, Byte *source, Size size) {
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

Byte *DataBytes(Data *buffer) {
  return buffer->bytes;
}

Size DataSize(Data *buffer) {
  return buffer->size;
}
