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

Bool SetDecode(Binary *binary, Integer32 *offset, Value **value) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return FALSE;
    Set *set = SetCreate(count);
    for (Integer32 index = 0; index < count; index += 1) {
        Value *value;
        if (!BinaryDecodeValue(binary, offset, &value))
            goto out;
        set->values[index] = value;
    }
    *value = ValueCreateSet(set);
    return TRUE;

out:
    SetDealloc(set);
    return FALSE;
}

Bool SetEval(Set *set, Context *context, Stack *stack) {
    Set *eval = SetCreate(set->count);
    for (Integer32 index = 0; index < set->count; index += 1) {
        if (!ValueEval(set->values[index], context, stack))
            goto out;
        eval->values[index] = StackPopValue(stack);
    }
    Value *value = ValueCreateSet(eval);
    StackReplaceTop(stack, value);
    return TRUE;

out:
    SetDealloc(eval);
    return FALSE;
}
 
Bool SetEqual(Set *set, Set *other) {
    if (set->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < set->count; index += 1)
        if (!ValueEqual(set->values[index], other->values[index]))
            return FALSE;
    return TRUE;
}
