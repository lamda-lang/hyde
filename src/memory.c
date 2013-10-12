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

void MemoryCopyUnit(void *source, void *target, Size unitSize) {
    memmove(target, source, unitSize);
}

void MemoryCopyArray(void *source, void *target, Size elementSize, Integer32 count) {
    MemoryCopyUnit(source, target, elementSize * count);
}

void MemoryCopyRegion(void *source, void *target, Size unitSize, Size elementSize, Integer32 count) {
    MemoryCopyUnit(source, target, unitSize + elementSize * count);
}

void MemoryDealloc(void *buffer) {
    free(buffer);
}
