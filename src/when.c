#include "when.h"

typedef struct {
    VALUE *condition;
    VALUE *value;
} Branch;

typedef struct {
    VALUE *type;
    Integer32 count;
    Branch branches[];
} When;

static When *WhenCreate(Integer32 count, VALUE **error) {
    When *block = MemoryAlloc(sizeof(When) + sizeof(Branch) * count, error);
    if (*error != NULL) {
        return NULL;
    }
    block->type = RuntimeWhenType;
    block->count = count;
    return block;
}

VALUE *WhenDecode(Byte **bytes, VALUE **error) {
    Integer32 count = DecodeInteger32(bytes);
    When *block = WhenCreate(count, error);
    if (*error != NULL) {
        goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
        block->branches[index].condition = DecodeValue(bytes, error);
        if (*error != NULL) {
            goto deallocWhen;
        }
        block->branches[index].value = DecodeValue(bytes, error);
        if (*error != NULL) {
            goto deallocWhen;
        }
    }
    return block;

deallocWhen:
    MemoryDealloc(block);
returnError:
    return NULL;
}
