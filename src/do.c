#include "do.h"

typedef struct {
  VALUE *type;
  Integer32 count;
  VALUE *elements[];
} Do;

static Do *DoCreate(Integer32 count, Error *error) {
    Do *block = MemoryAlloc(sizeof(Do) * sizeof(VALUE *) * count, error);
    if (*error != ErrorNone) {
        return NULL;
    }
    block->type = NULL;
    block->count = count;
    return block;
}

VALUE *DoDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Do *block = DoCreate(count, error);
    if (*error != ErrorNone) {
        goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
        block->elements[index] = DecodeValue(bytes, error);
        if (*error != ErrorNone) {
            goto deallocDo;
        }
    }
    return block;

deallocDo:
    MemoryDealloc(block);
returnError:
    return NULL;
}

void DoDealloc(VALUE *doValue) {
    MemoryDealloc(doValue);
}
