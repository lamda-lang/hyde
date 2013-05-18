#include "RTBuffer.h"

struct RTBuffer {
  RTByte *bytes;
  RTSize size;
};

RTBuffer *RTBufferCreate(void) {
  RTBuffer *buffer = RTMemoryAlloc(sizeof(RTBuffer));
  if (buffer == NULL) return NULL;
  buffer->bytes = NULL;
  buffer->size = 0;
  return buffer;
}

void RTBufferDealloc(RTBuffer *buffer) {
  RTMemoryDealloc(buffer->bytes);
  RTMemoryDealloc(buffer);
}

RTError RTBufferAppend(RTBuffer *buffer, RTByte *source, RTSize size) {
  RTByte *bytes = RTMemoryRealloc(buffer->bytes, buffer->size + size);
  if (bytes == NULL) return RTErrorOutOfMemory;
  RTByte *target = bytes + buffer->size;
  buffer->bytes = bytes;
  buffer->size += size;
  RTMemoryCopy(source, target, size);
  return RTErrorNone;
}

RTByte *RTBufferBytes(RTBuffer *buffer) {
  return buffer->bytes;
}

RTSize RTBufferSize(RTBuffer *buffer) {
  return buffer->size;
}
