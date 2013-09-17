#include <stdlib.h>
#include <string.h>
#include <posix/memory.h>

void *MemoryAlloc(Size size) {
    return malloc(size);
}

void *MemoryClone(void *buffer, Size size) {
    void *clone = malloc(size);
    if (clone == NULL)
        return NULL;
    memcpy(clone, buffer, size);
    return clone;
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
