#ifndef POSIX_MEMORY_H
#define POSIX_MEMORY_H

#include <posix/api.h>

void *MemoryAlloc(Size size, Error *error);
void *MemoryRealloc(void *buffer, Size size, Error *error);
void MemoryDealloc(void *buffer);
void MemoryCopy(void *source, void *target, Size size);
Bool MemoryEqual(void *buffer, void *other, Size size);

#endif
