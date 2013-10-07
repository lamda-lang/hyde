#include "case.h"

typedef struct Branch Branch;

struct Branch {
    Value *match;
    Value *guard;
    Value *value;
};

struct Case {
    Integer32 count;
    Value *arg;
    Branch branches[];
};

static Size CaseSizeOf(Integer32 count) {
    return sizeof(Case) + sizeof(Branch) * count;
}

static Case *CaseCreate(Value *arg, Integer32 count, Error *error) {
    Size size = CaseSizeOf(count);
    Case *block = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    block->arg = arg;
    block->count = count;
    return block;
}

Size CaseSize(Case *block) {
    Size size = ValueSize(block->arg) + INTEGER_32_SIZE;
    for (Integer32 index = 0; index < block->count; index += 1) {
        size += ValueSize(block->branches[index].match);
        size += ValueSize(block->branches[index].guard);
        size += ValueSize(block->branches[index].value);
    }
    return size;
}

Size CaseEncode(Case *block, Byte **bytes) {
    ValueEncode(block->arg, bytes);
    EncodeInteger32(block->count, bytes);
    for (Integer32 index = 0; index < block->count; index += 1) {
        ValueEncode(block->branches[index].match, bytes);
        ValueEncode(block->branches[index].guard, bytes);
        ValueEncode(block->branches[index].value, bytes);
    }
    return CaseSize(block);
}

Case *CaseDecode(Byte **bytes, Error *error) {
    Value *arg = ValueDecode(bytes, error);
    if (ERROR(error))
        return NULL;
    Integer32 count = DecodeInteger32(bytes);
    Case *block = CaseCreate(arg, count, error);
    if (ERROR(error))
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        block->branches[index].match = ValueDecode(bytes, error);
        if (ERROR(error))
            goto block;
        block->branches[index].guard = ValueDecode(bytes, error);
        if (ERROR(error))
            goto block;
        block->branches[index].value = ValueDecode(bytes, error);
        if (ERROR(error))
            goto block;
    }
    return block;

block:
    CaseRelease(block);
    return NULL;
}

Value *CaseEval(Value *value, Case *block, Value *context, Error *error) {
    Value *arg = ValueEval(block->arg, context, error);
    if (ERROR(error))
        return NULL;
    for (Integer32 index = 0; index < block->count; index += 1) {
        Value *match = ValueEval(block->branches[index].match, context, error);
        if (ERROR(error))
            return NULL;
        if (!ValueEqual(arg, match))
            continue;
        Value *guard = ValueEval(block->branches[index].guard, context, error);
        if (ERROR(error))
            return NULL;
        if (ValueIsTrue(guard))
            return ValueEval(block->branches[index].value, context, error);
    }
    *error = ERROR_NO_MATCH;
    return NULL;
}

Bool CaseEqual(Case *block, Case *other) {
    if (block->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < block->count; index += 1) {
        if (!ValueEqual(block->branches[index].match, other->branches[index].match))
            return FALSE;
        if (!ValueEqual(block->branches[index].guard, other->branches[index].guard))
            return FALSE;
        if (!ValueEqual(block->branches[index].value, other->branches[index].value))
            return FALSE;
    }
    return TRUE;
}

Size CaseRelease(Case *block) {
    Size size = CaseSizeOf(block->count);
    MemoryDealloc(block);
    return size;
}
