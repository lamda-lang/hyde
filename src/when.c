#include "when.h"

typedef struct {
    Value *condition;
    Value *value;
} Branch;

struct When {
    Integer32 count;
    Branch branches[];
};

static When *WhenCreate(Integer32 count) {
    When *block = MemoryAllocRegion(sizeof(When), sizeof(Branch), count);
    block->count = count;
    return block;
}

static void WhenDealloc(When *block) {
    MemoryDealloc(block);
}

Value *WhenDecodePrimitive(Binary *binary, Integer32 *offset) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return NULL;
    Value *arg = BinaryDecodeValue(binary, offset);
    if (arg == NULL)
        return NULL;
    When *block = WhenCreate(count);
    for (Integer32 index = 0; index < count; index += 1) {
        Value *condition = BinaryDecodeValue(binary, offset);
        if (condition == NULL)
            goto out;
        Value *value = BinaryDecodeValue(binary, offset);
        if (value == NULL)
            goto out;
        block->branches[index].condition = condition;
        block->branches[index].value = value;
    }
    return ValueCreateWhen(block);

out:
    WhenDealloc(block);
    return NULL;
}
