#ifndef MEMORY_H
#define MEMORY_H

#include "api.h"

void *MemoryAlloc(Size size, Error *error);
void *MemoryRealloc(void *buffer, Size size, Error *error);
void MemoryDealloc(void *buffer);
void MemoryCopy(void *source, void *target, Size size);
bool MemoryEqual(void *buffer, void *other, Size size);

#endif
