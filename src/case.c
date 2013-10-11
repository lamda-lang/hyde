#include "case.h"

typedef struct {
    Value *match;
    Value *guard;
    Value *value;
} Branch;

struct Case {
    Integer32 count;
    Value *arg;
    Branch branches[];
};

static Case *CaseCreate(Integer32 count) {
    Case *block = MemoryAllocRegion(sizeof(Case), sizeof(Branch), count);
    block->count = count;
    return block;
}

static void CaseDealloc(Case *block) {
    MemoryDealloc(block);
}

Value *CaseDecodePrimitive(Binary *binary, Integer32 *offset) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return NULL;
    Value *arg = BinaryDecodeValue(binary, offset);
    if (arg == NULL)
        return NULL;
    Case *block = CaseCreate(count, arg);
    for (Integer32 index = 0; index < count; index += 1) {
        Value *match = BinaryDecodeValue(binary, offset);
        if (match == NULL)
            goto out;
        Value *guard = BinaryDecodeValue(binary, offset);
        if (guard == NULL)
            goto out;
        Value *match = BinaryDecodeValue(binary, offset);
        if (match == NULL)
            goto out;
        block->branches[index].match = match;
        block->branches[index].guard = guard;
        block->branches[index].value = value;
    }
    return ValueCreateCase(block);

out:
    CaseDealloc(block);
    return NULL;
}
