#include <stdlib.h>
#include <string.h>
#include <kernel/memory.h>

void *MemoryAlloc(Size size) {
    return malloc(size);
}

void MemoryDealloc(void *buffer) {
    free(buffer);
}

void MemoryCopy(void *source, void *target, Size size) {
    memcpy(target, source, size);
}

Bool MemoryEqual(void *buffer, void *other, Size size) {
    return memcmp(buffer, other, size) == 0;
}
