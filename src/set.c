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

void *SetDecode(Byte **bytes, VALUE **error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer32) * count, error);
    if (model == NULL) {
        goto returnVALUE;
    }
    model->count = count;
    for (Integer32 index = 0; index < count; index += 1) {
        model->element[index] = DecodeInteger32VLE(bytes);
    }
    return model;

returnVALUE:
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
