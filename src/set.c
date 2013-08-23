#include "api.h"

struct Set {
    Type *type;
    Integer32 count;
    Value *element[];
};

typedef struct {
    Integer32 count;
    Integer32 element[];
} Model;

static Set *Create(Integer32 count, Value **error) {
    Set *set = MemoryAlloc(sizeof(Set) + sizeof(Value *) * count, error);
    if (set == NULL) {
        goto returnValue;
    }
    set->type = TypeSet;
    set->count = count;
    return set;

returnValue:
    return NULL;
}

void *SetDecode(Byte **bytes, Value **error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer32) * count, error);
    if (model == NULL) {
        goto returnValue;
    }
    model->count = count;
    for (Integer32 index = 0; index < count; index += 1) {
        model->element[index] = DecodeInteger32VLE(bytes);
    }
    return model;

returnValue:
    return NULL;
}

void SetDealloc(Value *setValue) {
    MemoryDealloc(setValue);
}

Integer64 SetHash(Value *setValue) {
    return BridgeToSet(setValue)->count;
}

void SetEnumerate(Value *setValue, void (*callback)(Value *value)) {
    Set *set = BridgeToSet(setValue);
    for (Integer32 index = 0; index < set->count; index += 1) {
        callback(set->element[index]);
    }
}
