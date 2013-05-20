#include "RTBuffer.h"

struct RTBuffer {
  RTByte *bytes;
  RTSize size;
};

RTBuffer *RTBufferCreate(void) {
  RTBuffer *buffer = RTMemoryAlloc(sizeof(RTBuffer));
  if (buffer == NULL) {
    goto error;
  }
  buffer->bytes = NULL;
  buffer->size = 0;
  return buffer;

error:
  return NULL;
}

void RTBufferDealloc(RTBuffer *buffer) {
  RTMemoryDealloc(buffer->bytes);
  RTMemoryDealloc(buffer);
}

RTStatus RTBufferAppend(RTBuffer *buffer, RTByte *source, RTSize size) {
  RTByte *bytes = RTMemoryRealloc(buffer->bytes, buffer->size + size);
  if (bytes == NULL) {
    goto error;
  }
  RTByte *target = bytes + buffer->size;
  buffer->bytes = bytes;
  buffer->size += size;
  RTMemoryCopy(source, target, size);
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}

RTByte *RTBufferBytes(RTBuffer *buffer) {
  return buffer->bytes;
}

RTSize RTBufferSize(RTBuffer *buffer) {
  return buffer->size;
}
