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

VALUE *DoDecode(Byte **bytes, VALUE **error) {
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
