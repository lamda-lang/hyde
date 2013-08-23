#include <stdlib.h>
#include <string.h>
#include "memory.h"

void *MemoryAlloc(Size size, VALUE **error) {
    void *buffer = malloc(size);
    if (buffer == NULL) {
        *error = TokenOutOfMemoryError;
    }
    return buffer;
}

void *MemoryRealloc(void *buffer, Size size, VALUE **error) {
    void *new = realloc(buffer, size);
    if (new == NULL) {
        *error = TokenOutOfMemoryError;
    }
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
