#include <builtin/case.h>

typedef struct Branch Branch;

struct Branch {
    Value *match;
    Value *guard;
    Value *value;
};

struct Case {
    Integer32 count;
    Branch branches[];
};

static Case *CaseCreate(Integer32 count) {
    Case *block = MemoryAlloc(sizeof(Case) + sizeof(Branch) * count);
    if (block == NULL)
        return NULL;
    block->count = count;
    return block;
}

Value *CaseDecode(Byte **bytes) {
    Integer32 count = DecodeInteger32(bytes);
    Case *block = CaseCreate(count);
    if (block == NULL)
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        Value *match = ValueDecode(bytes);
        if (match == NULL)
            return CaseRelease(block), NULL;
        Value *guard = ValueDecode(bytes);
        if (guard == NULL)
            return CaseRelease(block), NULL;
        Value *value = ValueDecode(bytes);
        if (value == NULL)
            return CaseRelease(block), NULL;
        block->branches[index].match = match;
        block->branches[index].guard = guard;
        block->branches[index].value = value;
    }
    return ValueCreate(MODEL_CASE, block);
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
    Integer32 count = block->count;
    MemoryDealloc(block);
    return sizeof(Case) + sizeof(Branch) * count;
}
