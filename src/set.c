#include "api.h"

struct Set {
    Value base;
    Integer32 length;
    Value *element[];
};

static Integer32 IndexForValue(Set *set, Value *value, Integer32 offset) {
    return (ValueHash(value) + offset) % set->length;
}

static Set *Create(Integer32 count, Error *error) {
    Integer32 length = count << 1;
    Size size = sizeof(Set) + sizeof(Value *) * length;
    Set *set = MemoryAlloc(size, error);
    if (set == NULL) {
        goto returnError;
    }
    set->base = TypeSet;
    set->length = length;
    for (Integer32 index = 0; index < length; index += 1) {
        set->element[index] = NULL;
    }
    return set;

returnError:
    return NULL;
}

Set *SetDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    return Create(count, error);
}

Integer32 SetCount(Set *set) {
    return set->length;
}

void SetAddValue(Set *set, Value *value) {
    Integer32 index = IndexForValue(set, value, 0);
    while (set->element[index] != NULL) {
        index = IndexForValue(set, value, index);
    }
    set->element[index] = value;
}

Value *SetValueBridge(Set *set) {
    return (Value *)set;
}

void SetDealloc(Value *setValue) {
    MemoryDealloc(setValue);
}

Integer64 SetHash(Value *setValue) {
    return  ValueSetBridge(setValue, NULL)->length;
}

void SetEnumerate(Value *setValue, void (*block)(Value *value)) {
    Set *set = ValueSetBridge(setValue, NULL);
    for (Integer32 index = 0; index < set->length; index += 1) {
        block(set->element[index]);
    }
}