#include "memory.h"

void *MemoryAlloc(Size size, Error *error) {
    void *buffer = malloc(size);
    if (buffer == NULL && error != NULL)
        goto error;
    return buffer;

error:
    *error = ERROR_OF_OF_MEMORY;
    return NULL;
}

void *MemoryClone(void *buffer, Size size, Error *error) {
    void *clone = malloc(size);
    if (clone == NULL && error != NULL)
        goto error;
    memcpy(clone, buffer, size);
    return clone;

error:
    *error = ERROR_OF_OF_MEMORY;
    return NULL;
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
