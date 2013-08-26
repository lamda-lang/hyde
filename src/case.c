#include "case.h"

typedef struct {
    VALUE *match;
    VALUE *guard;
    VALUE *value;
} Branch;

struct Case {
    Type *type;
    Integer32 count;
    Branch branches[];
};

static Case *CaseCreate(Integer32 count, VALUE **error) {
    Case *block = MemoryAlloc(sizeof(Case) + sizeof(Branch) * count, error);
    if (*error != NULL) {
        return NULL;
    }
    block->type = RuntimeCaseType;
    block->count = count;
    return block;
}

VALUE *CaseDecode(Byte **bytes, VALUE **error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Case *block = CaseCreate(count, error);
    if (*error != NULL) {
        goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
        block->branches[index].match = DecodeValue(bytes, error);
        if (*error != NULL) {
            goto deallocCase;
        }
        block->branches[index].guard = DecodeValue(bytes, error);
        if (*error != NULL) {
            goto deallocCase;
        }
        block->branches[index].value = DecodeValue(bytes, error);
        if (*error != NULL) {
            goto deallocCase;
        }
    }
    return BridgeFromCase(block);

deallocCase:
    MemoryDealloc(block);
returnError:
    return NULL;
}
