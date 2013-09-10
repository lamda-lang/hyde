#ifndef KERNEL_MEMORY_H
#define KERNEL_MEMORY_H

#include <runtime.h>

void *MemoryAlloc(Size size);
void MemoryDealloc(void *buffer);
void MemoryCopy(void *source, void *target, Size size);
Bool MemoryEqual(void *buffer, void *other, Size size);

#endif
