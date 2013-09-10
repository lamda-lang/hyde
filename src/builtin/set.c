#include <builtin/set.h>

typedef struct Set Set;

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
        if (ValueEqual(value, set->values[index])
            return TRUE
    return FALSE;
}

Value *SetDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Set *set = SetCreate(count);
    if (set == NULL)
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        Value *value = DecodeValue(bytes, error);
        if (value == NULL)
            return SetRelease(set), NULL;
        set->values[index] = value;
    }
    return ValueCreate(ModelSet, set);
}

void SetRelease(void *setData) {
    MemoryDealloc(setData);
}

Bool SetEqual(void *setData, void *otherData) {
    Set *set = setData;
    Set *other = otherData;
    if (set->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < set->count; index += 1)
        if (!SetElement(other, set->values[index])
            return FALSE;
    return TRUE;
}
