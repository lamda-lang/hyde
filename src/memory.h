#ifndef MEMORY_H
#define MEMORY_H

#include "runtime.h"

void *MemoryAllocUnit(Size unitSize);
void *MemoryAllocArray(Size elementSize, Integer32 count);
void *MemoryAllocRegion(Size unitSize, Size elementSize, Integer32 count);
void MemoryCopyUnit(void *source, void *target, Size unitSize);
void MemoryCopyArray(void *source, void *target, Size elementSize, Integer32 count);
void MemoryCopyRegion(void *source, void *target, Size unitSize, Size elementSize, Integer32 count);
void MemoryDealloc(void *buffer);

#endif
