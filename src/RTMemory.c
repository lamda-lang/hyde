#include "RTMemory.h"

void *RTMemoryAlloc(RTSize size) {
  return malloc(size);
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
