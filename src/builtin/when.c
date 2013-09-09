#include <builtin/when.h>

typedef struct Branch Branch;
typedef struct When When;

struct Branch {
    Value *condition;
    Value *value;
};

struct When {
    Value *type;
    Integer32 count;
    Branch branches[];
};

static When *WhenCreate(Integer32 count, Error *error) {
    When *block = MemoryAlloc(sizeof(When) + sizeof(Branch) * count, error);
    if (*error != ErrorNone)
        return NULL;
    block->type = NULL;
    block->count = count;
    return block;
}

Value *WhenDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    When *block = WhenCreate(count, error);
    if (*error != ErrorNone) goto returnError;
    for (Integer32 index = 0; index < count; index += 1) {
        block->branches[index].condition = DecodeValue(bytes, error);
        if (*error != ErrorNone) goto deallocWhen;
        block->branches[index].value = DecodeValue(bytes, error);
        if (*error != ErrorNone) goto deallocWhen;
    }
    return block;

deallocWhen:
    MemoryDealloc(block);
returnError:
    return NULL;
}
