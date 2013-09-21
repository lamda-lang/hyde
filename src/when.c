#include "when.h"

typedef struct Branch Branch;

struct Branch {
    Value *condition;
    Value *value;
};

struct When {
    Integer32 count;
    Branch branches[];
};

static When *WhenCreate(Integer32 count) {
    When *block = MemoryAlloc(sizeof(When) + sizeof(Branch) * count);
    if (block == NULL)
        return NULL;
    block->count = count;
    return block;
}

When *WhenDecode(Byte **bytes) {
    Integer32 count = DecodeInteger32(bytes);
    When *block = WhenCreate(count);
    if (block == NULL)
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        Value *condition = ValueDecode(bytes);
        if (condition == NULL)
            return WhenRelease(block), NULL;
        Value *value = ValueDecode(bytes);
        if (value == NULL)
            return WhenRelease(block), NULL;
        block->branches[index].condition = condition;
        block->branches[index].value = value;
    }
    return block;
}

Value *WhenEval(When *block, Value *context) {
    for (Integer32 index = 0; index < block->count; index += 1) {
        Value *condition = ValueEval(block->branches[index].condition, context);
        if (condition == NULL)
            return NULL;
        if (condition == VALUE_TRUE)
            return ValueEval(block->branches[index].value, context);
    }
    return VALUE_NIL;
}

Bool WhenEqual(When *block, When *other) {
    if (block->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < block->count; index += 1) {
        if (!ValueEqual(block->branches[index].condition, other->branches[index].condition))
            return FALSE;
        if (!ValueEqual(block->branches[index].value, other->branches[index].value))
            return FALSE;
    }
    return TRUE;
}

Size WhenRelease(When *block) {
    Integer32 count = block->count;
    MemoryDealloc(block);
    return sizeof(When) + sizeof(Branch) * count;
}
