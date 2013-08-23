#include "do.h"

typedef struct {
    Integer32 count;
    Integer32 element[];
} Model;

struct Do {
  Type *type;
  Integer32 count;
  Value *element[];
};

static Do *Create(Integer32 count, Value **error) {
    Do *block = MemoryAlloc(sizeof(Do) * sizeof(Value *) * count, error);
    if (block == NULL) {
        goto returnValue;
    }
    block->type = TypeDo;
    block->count = count;
    return block;

returnValue:
    return NULL;
}

void *DoDecode(Byte **bytes, Value **error) {
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

void DoDealloc(Value *doValue) {
    MemoryDealloc(doValue);
}

Integer64 DoHash(Value *doValue) {
    return BridgeToDo(doValue)->count;
}

void DoEnumerate(Value *doValue, void (*callback)(Value *value)) {
    Do *block = BridgeToDo(doValue);
    for (Integer32 index = 0; index < block->count; index += 1) {
        callback(block->element[index]);
    }
}
