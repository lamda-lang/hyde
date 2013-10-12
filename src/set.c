#include "set.h"

struct Set {
    Integer32 count;
    Value *values[];
};

static Set *SetCreate(Integer32 count) {
    Set *set = MemoryAllocRegion(sizeof(Set), sizeof(Value *), count);
    set->count = count;
    return set;
}

static void SetDealloc(Set *set) {
    MemoryDealloc(set);
}

Value *SetDecodePrimitive(Binary *binary, Integer32 *offset) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return NULL;
    Set *set = SetCreate(count);
    for (Integer32 index = 0; index < count; index += 1) {
        Value *value = BinaryDecodeValue(binary, offset);
        if (value == NULL)
            goto out;
        set->values[index] = value;
    }
    return ValueCreateSet(set);

out:
    SetDealloc(set);
    return NULL;
}
