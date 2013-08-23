#ifndef MEMORY_H
#define MEMORY_H

#include "api.h"

void *MemoryAlloc(Size size, Value **error);
void *MemoryRealloc(void *buffer, Size size, Value **error);
void MemoryDealloc(void *buffer);
void MemoryCopy(void *source, void *target, Size size);
Bool MemoryEqual(void *buffer, void *other, Size size);

#endif
