#include "RTMemory.h"

void *RTMemoryAlloc(RTSize size) {
  return malloc(size);
}

void *RTMemoryRealloc(void *buffer, RTSize size) {
  return realloc( buffer, size);
}

void RTMemoryDealloc(void *buffer) {
  free(buffer);
}

void RTMemoryCopy(void *source, void *target, RTSize size) {
  memcpy(target, source, size);
}

RTBool RTMemoryCompare(void *buffer, void *other, RTSize size) {
  return memcmp(buffer, other, size) == 0;
}
