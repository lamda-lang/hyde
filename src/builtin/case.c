#include <builtin/case.h>

typedef struct Branch Branch;

struct Branch {
    Value *match;
    Value *guard;
    Value *value;
};

struct Case {
    Value value;
    Integer32 count;
    Branch branches[];
};

static Value *CaseToValue(Case *block) {
    return (Value *)block;
}

static Case *CaseFromValue(Value *value) {
    return (Case *)value;
}

static Case *CaseCreate(Integer32 count, Error *error) {
    Case *block = MemoryAlloc(sizeof(Case) + sizeof(Branch) * count, error);
    if (*error != ErrorNone)
        return NULL;
    block->value = ValueCase;
    block->count = count;
    return block;
}

static Value *CaseDealloc(Case *block) {
    MemoryDealloc(block);
    return NULL;
}

Value *CaseDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Case *block = CaseCreate(count, error);
    if (*error != ErrorNone)
        return CaseDealloc(block);
    for (Integer32 index = 0; index < count; index += 1) {
        block->branches[index].match = DecodeValue(bytes, error);
        if (*error != ErrorNone)
            return CaseDealloc(block);
        block->branches[index].guard = DecodeValue(bytes, error);
        if (*error != ErrorNone)
            return CaseDealloc(block);
        block->branches[index].value = DecodeValue(bytes, error);
        if (*error != ErrorNone)
            return CaseDealloc(block);
    }
    return block;
}

Bool CaseEqual(Value *caseValue, Value *otherValue) {
    if (caseValue == otherValue)
        return TRUE;
    Case *block = caseValue;
    Case *other = otherValue;
    if (block->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < block->count; index += 1) {
        if (!Equal(block->branches[index].match, other->branches[index].match))
            return FALSE;
        if (!Equal(block->branches[index].guard, other->branches[index].guard))
            return FALSE;
        if (!Equal(block->branches[index].value, other->branches[index].value))
            return FALSE;
    }
    return TRUE;
}

void CaseRelease(Value *caseValue) {
    CaseDealloc(caseValue);
}
