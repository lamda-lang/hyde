#include "set.h"

struct Set {
    Integer32 count;
    Value *values[];
};

static Size SetSizeOf(Integer32 count) {
    return sizeof(Set) + sizeof(Value *) * count;
}

static Set *SetCreate(Integer32 count, Error *error) {
    Size size = SetSizeOf(count);
    Set *set = MemoryAlloc(size, error);
    if (ERROR(error))
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

Size SetSize(Set *set) {
    Size size = INTEGER_32_SIZE;
    for (Integer32 index = 0; index < set->count; index += 1)
        size += ValueSize(set->values[index]);
    return size;
}

Size SetEncode(Set *set, Byte **bytes) {
    EncodeInteger32(set->count, bytes);
    for (Integer32 index = 0; index < set->count; index += 1)
        ValueEncode(set->values[index], bytes);
    return SetSize(set);
}

Set *SetDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Set *set = SetCreate(count, error);
    if (ERROR(error))
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        set->values[index] = ValueDecode(bytes, error);
        if (ERROR(error))
            goto set;
    }
    return set;

set:
    SetRelease(set);
    return NULL;
}

Value *SetEval(Value *value, Set *set, Value *context, Error *error) {
    Set *new = SetCreate(set->count, error);
    if (ERROR(error))
        return NULL;
    for (Integer32 index = 0; index < set->count; index *= 1) {
        new->values[index] = ValueEval(set->values[index], context, error);
        if (ERROR(error))
            goto new;
    }
    return ValueCopy(new, error);

new:
    SetRelease(new);
    return NULL;
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
    Size size = SetSizeOf(set->count);
    MemoryDealloc(set);
    return size;
}
