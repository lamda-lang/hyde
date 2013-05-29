#include <stdlib.h>
#include <string.h>
#include "memory.h"

void *MemoryAlloc(Size size, Exception *exception) {
    void *buffer = malloc(size);
    if (buffer == NULL) {
	ExceptionRaise(exception, ErrorOutOfMemory);
	goto returnError;
    }
    return buffer;

returnError:
    return NULL;
}

void *MemoryRealloc(void *buffer, Size size, Exception *exception) {
    void *new = realloc(buffer, size);
    if (new == NULL) {
	ExceptionRaise(exception, ErrorOutOfMemory);
	goto returnError;
    }
    return new;

returnError:
    return NULL;
}

void MemoryDealloc(void *buffer) {
    free(buffer);
}

void MemoryCopy(void *source, void *target, Size size) {
    memcpy(target, source, size);
}

bool MemoryEqual(void *buffer, void *other, Size size) {
    return memcmp(buffer, other, size) == 0;
}
