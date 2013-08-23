#include "do.h"

typedef struct {
    Integer32 count;
    Integer32 element[];
} Model;

struct Do {
  Type *type;
  Integer32 count;
  VALUE *element[];
};

static Do *Create(Integer32 count, VALUE **error) {
    Do *block = MemoryAlloc(sizeof(Do) * sizeof(VALUE *) * count, error);
    if (block == NULL) {
        goto returnVALUE;
    }
    block->type = TypeDo;
    block->count = count;
    return block;

returnVALUE:
    return NULL;
}

void *DoDecode(Byte **bytes, VALUE **error) {
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

void DoDealloc(VALUE *doVALUE) {
    MemoryDealloc(doVALUE);
}

Integer64 DoHash(VALUE *doVALUE) {
    return BridgeToDo(doVALUE)->count;
}

void DoEnumerate(VALUE *doVALUE, void (*callback)(VALUE *value)) {
    Do *block = BridgeToDo(doVALUE);
    for (Integer32 index = 0; index < block->count; index += 1) {
        callback(block->element[index]);
    }
}
