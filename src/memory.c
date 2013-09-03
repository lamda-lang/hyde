#include "memory.h"

void *MemoryAlloc(Size size, Error *error) {
    void *buffer = malloc(size);
    if (buffer == NULL) *error = ErrorOutOfMemory;
    return buffer;
}

void *MemoryRealloc(void *buffer, Size size, Error *error) {
    void *new = realloc(buffer, size);
    if (new == NULL) *error = ErrorOutOfMemory;
    return new;
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
