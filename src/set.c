#include "api.h"

typedef struct {
    VALUE *type;
    Integer32 count;
    VALUE *elements[];
} Set;

static Set *SetCreate(Integer32 count, Error *error) {
    Set *set = MemoryAlloc(sizeof(Set) + sizeof(VALUE *) * count, error);
    if (*error != ErrorNone) {
        return NULL;
    }
    set->type = NULL;
    set->count = count;
    return set;
}

VALUE *SetDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Set *set = SetCreate(count, error);
    if (*error != ErrorNone) {
        goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
        set->elements[index] = DecodeValue(bytes, error);
        if (*error != ErrorNone) {
            goto deallocSet;
        }
    }
    return set;

deallocSet:
    MemoryDealloc(set);
returnError:
    return NULL;
}

void SetDealloc(VALUE *setValue) {
    MemoryDealloc(setValue);
}
