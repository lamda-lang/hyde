#include "runtime.h"

struct Set {
    Type *type;
    Integer32 count;
    VALUE *element[];
};

typedef struct {
    Integer32 count;
    Integer32 element[];
} Model;

static Set *Create(Integer32 count, VALUE **error) {
    Set *set = MemoryAlloc(sizeof(Set) + sizeof(VALUE *) * count, error);
    if (set == NULL) {
        goto returnVALUE;
    }
    set->type = TypeSet;
    set->count = count;
    return set;

returnVALUE:
    return NULL;
}

VALUE *SetDecode(Byte **bytes, VALUE **error) {
    return NULL;
}

void SetDealloc(VALUE *setVALUE) {
    MemoryDealloc(setVALUE);
}

Integer64 SetHash(VALUE *setVALUE) {
    return BridgeToSet(setVALUE)->count;
}

void SetEnumerate(VALUE *setVALUE, void (*callback)(VALUE *value)) {
    Set *set = BridgeToSet(setVALUE);
    for (Integer32 index = 0; index < set->count; index += 1) {
        callback(set->element[index]);
    }
}
