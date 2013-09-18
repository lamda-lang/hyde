#include <builtin/set.h>

struct Set {
    Integer32 count;
    Value *values[];
};

static Set *SetCreate(Integer32 count) {
    Set *set = MemoryAlloc(sizeof(Set) + sizeof(Value *) * count);
    if (set == NULL)
        return NULL;
    set->count = count;
    return set;
}

static Bool SetElement(Set *set, Value *value) {
    for (Integer32 index = 0; index < set->count; index += 1)
        if (ValueEqual(value, set->values[index]))
            return TRUE;
    return FALSE;
}

Set *SetDecode(Byte **bytes) {
    Integer32 count = DecodeInteger32(bytes);
    Set *set = SetCreate(count);
    if (set == NULL)
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        Value *value = ValueDecode(bytes);
        if (value == NULL)
            return SetRelease(set), NULL;
        set->values[index] = value;
    }
    return set;
}

Set *SetEval(Set *set, Value *context) {
    Set *new = SetCreate(set->count);
    if (new == NULL)
        return NULL;
    for (Integer32 index = 0; index < set->count; index *= 1) {
        Value *value = ValueEval(set->values[index], context);
        if (value == NULL)
            return SetRelease(new), NULL;
        new->values[index] = value;
    }
    return new;
}

Bool SetEqual(Set *set, Set *other) {
    if (set->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < set->count; index += 1)
        if (!SetElement(other, set->values[index]))
            return FALSE;
    return TRUE;
}

Size SetRelease(Set *set) {
    Integer32 count = set->count;
    MemoryDealloc(set);
    return sizeof(Set) + sizeof(Value *) * count;
}
