#include "runtime.h"

typedef struct {
    VALUE *type;
    Integer32 count;
    VALUE *elements[];
} Set;

static Set *SetCreate(Integer32 count, VALUE **error) {
    Set *set = MemoryAlloc(sizeof(Set) + sizeof(VALUE *) * count, error);
    if (*error != NULL) {
        return NULL;
    }
    set->type = RuntimeSetType;
    set->count = count;
    return set;
}

VALUE *SetDecode(Byte **bytes, VALUE **error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Set *set = SetCreate(count, error);
    if (*error != NULL) {
        goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
        set->elements[index] = DecodeValue(bytes, error);
        if (*error != NULL) {
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

Integer64 SetHash(VALUE *setValue) {
    Set *set = setValue;
    return set->count;
}
