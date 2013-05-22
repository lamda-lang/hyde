#include <stdlib.h>
#include <string.h>
#include "memory.h"

void *MemoryAlloc(Size size) {
  return malloc(size);
}

void *MemoryRealloc(void *buffer, Size size) {
  return realloc( buffer, size);
}

void MemoryDealloc(void *buffer) {
  free(buffer);
}

void MemoryCopy(void *source, void *target, Size size) {
  memcpy(target, source, size);
}

bool MemoryEqual(void *buffer, void *other, Size size) {
  return memcmp(buffer, other, size) == 0;
}
