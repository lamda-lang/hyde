#ifndef MEMORY_H
#define MEMORY_H

#include "runtime.h"

void *MemoryAllocUnit(Size unitSize);
void *MemoryAllocArray(Size elementSize, Integer32 count);
void *MemoryAllocRegion(Size unitSize, Size elementSize, Integer32 count);
void MemoryDealloc(void *buffer);

#endif
