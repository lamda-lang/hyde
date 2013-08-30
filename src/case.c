#include "case.h"

typedef struct {
    VALUE *match;
    VALUE *guard;
    VALUE *value;
} Branch;

typedef struct {
    VALUE *type;
    Integer32 count;
    Branch branches[];
} Case;

static Case *CaseCreate(Integer32 count, Error *error) {
    Case *block = MemoryAlloc(sizeof(Case) + sizeof(Branch) * count, error);
    if (*error != ErrorNone) {
        return NULL;
    }
    block->type = NULL;
    block->count = count;
    return block;
}

VALUE *CaseDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Case *block = CaseCreate(count, error);
    if (*error != ErrorNone) {
        goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
        block->branches[index].match = DecodeValue(bytes, error);
        if (*error != ErrorNone) {
            goto deallocCase;
        }
        block->branches[index].guard = DecodeValue(bytes, error);
        if (*error != ErrorNone) {
            goto deallocCase;
        }
        block->branches[index].value = DecodeValue(bytes, error);
        if (*error != ErrorNone) {
            goto deallocCase;
        }
    }
    return block;

deallocCase:
    MemoryDealloc(block);
returnError:
    return NULL;
}
