#include "api.h"

struct Set {
    Value base;
    Integer32 count;
    Value *element[];
};

typedef struct {
    Integer32 count;
    Integer32 element[];
} Model;

static Set *Create(Integer32 count, Error *error) {
    Set *set = MemoryAlloc(sizeof(Set) + sizeof(Value *) * count, error);
    if (set == NULL) {
        goto returnError;
    }
    set->base = TypeSet;
    set->count = count;
    return set;

returnError:
    return NULL;
}

void *SetDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer32) * count, error);
    if (model == NULL) {
        goto returnError;
    }
    model->count = count;
    for (Integer32 index = 0; index < count; index += 1) {
        model->element[index] = DecodeInteger32VLE(bytes);
    }
    return model;

returnError:
    return NULL;
}

Value *SetEval(void *data, Code *code, Value **context, Bool pure, Error *error) {
    Model *model = data;
    Set *set = Create(model->count, error);
    if (set == NULL) {
        goto returnError;
    }
    Value *setValue = BridgeFromSet(set);
    for (Integer32 index = 0; index < model->count; index += 1) {
        Value *value = CodeEvalInstructionAtIndex(code, context, model->element[index], TRUE, error);
        if (value == NULL) {
            goto deallocSet;
        }
        set->element[index] = value;
    }
    return setValue;

deallocSet:
    SetDealloc(setValue);
returnError:
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
