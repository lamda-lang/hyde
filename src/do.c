#include "do.h"

struct Do {
  Type *type;
  Integer32 count;
  VALUE *elements[];
};

static Do *DoCreate(Integer32 count, VALUE **error) {
    Do *block = MemoryAlloc(sizeof(Do) * sizeof(VALUE *) * count, error);
    if (*error != NULL) {
        return NULL;
    }
    block->type = TypeDo;
    block->count = count;
    return block;
}

VALUE *DoDecode(Byte **bytes, VALUE **error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Do *block = DoCreate(count, error);
    if (*error != NULL) {
        goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
        block->elements[index] = DecodeValue(bytes, error);
        if (*error != NULL) {
            goto deallocDo;
        }
    }
    return BridgeFromDo(block);

deallocDo:
    MemoryDealloc(block);
returnError:
    return NULL;
}

void DoDealloc(VALUE *doValue) {
    MemoryDealloc(doValue);
}

Integer64 DoHash(VALUE *doValue) {
    return BridgeToDo(doValue)->count;
}
