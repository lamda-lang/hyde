#include "memory.h"

void *MemoryAllocUnit(Size unitSize) {
    void *buffer = malloc(unitSize);
    if (buffer == NULL)
        abort();
    return buffer;
}

void *MemoryAllocArray(Size elementSize, Integer32 count) {
    return MemoryAllocUnit(elementSize * count);
}

void *MemoryAllocRegion(Size unitSize, Size elementSize, Integer32 count) {
    return MemoryAllocUnit(unitSize + elementSize * count);
}

void MemoryDealloc(void *buffer) {
    free(buffer);
}
