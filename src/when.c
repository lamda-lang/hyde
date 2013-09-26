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

static Size WhenSizeOf(Integer32 count) {
    return sizeof(When) + sizeof(Branch) * count;
}

static When *WhenCreate(Integer32 count, Error *error) {
    Size size = WhenSizeOf(count);
    When *block = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    block->count = count;
    return block;
}

Size WhenSize(When *block) {
    Size size = INTEGER_32_SIZE;
    for (Integer32 index = 0; index < block->count; index += 1) {
        size += ValueSize(block->branches[index].condition);
        size += ValueSize(block->branches[index].value);
    }
    return size;
}

Size WhenEncode(When *block, Byte **bytes) {
    EncodeInteger32(block->count, bytes);
    for (Integer32 index = 0; index < block->count; index += 1) {
        ValueEncode(block->branches[index].condition, bytes);
        ValueEncode(block->branches[index].value, bytes);
    }
    return WhenSize(block);
}

When *WhenDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    When *block = WhenCreate(count, error);
    if (ERROR(error))
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        block->branches[index].condition = ValueDecode(bytes, error);
        if (ERROR(error))
            goto block;
        block->branches[index].value = ValueDecode(bytes, error);
        if (ERROR(error))
            goto block;
    }
    return block;

block:
    WhenRelease(block);
    return NULL;
}

Value *WhenEval(When *block, Value *context, Error *error) {
    for (Integer32 index = 0; index < block->count; index += 1) {
        Value *condition = ValueEval(block->branches[index].condition, context, error);
        if (ERROR(error))
            return NULL;
        if (condition == ConstantValue(CONSTANT_BOOLEAN_TRUE))
            return ValueEval(block->branches[index].value, context, error);
    }
    return ConstantValue(CONSTANT_NIL);
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
    Size size = WhenSizeOf(block->count);
    MemoryDealloc(block);
    return size;
}
