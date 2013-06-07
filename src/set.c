#include "api.h"

struct Set {
    Value base;
    Integer32 capacity;
    Element element[];
};

static Integer32 IndexForValue(Set *set, Value *value, Integer32 offset) {
    return (ValueHash(value) + offset) % set->capacity;
}

static void AddValue(Set *set, Value *value) {
    Integer32 index = IndexForValue(set, value, 0);
    while (set->element[index].value != NULL) {
	index = IndexForValue(set, value, index);
    }
    set->element[index].value = value;
}

static Set *Create(Integer32 count, Error *error) {
    Integer32 capacity = count << 1;
    Size size = sizeof(Set) + sizeof(Element) * capacity;
    Set *set = MemoryAlloc(size, error);
    if (set == NULL) {
        goto returnError;
    }
    set->base = TypeSet;
    set->capacity = capacity;
    return set;

returnError:
    return NULL;
}

Value *SetDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Set *set = Create(count, error);
    if (set == NULL) {
	goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
	set->element[index].index = DecodeInteger32VLE(bytes);
    }
    return SetValueBridge(set);

returnError:
    return NULL;
}

void SetFetch(Value *setValue, Byte **values) {
    Set *set = ValueSetBridge(setValue, NULL);
    Integer32 count = set->capacity >> 1;
    Element element[count];
    Size size = sizeof(element);
    MemoryCopy(set->element, element, size);
    for (Integer32 index = 0; index < count; index += 1) {
	Integer32 elementIndex = element[index].index;
	AddValue(set, values[elementIndex]);
    }
}

Value *SetValueBridge(Set *set) {
    return (Value *)set;
}

void SetDealloc(Value *setValue) {
    MemoryDealloc(setValue);
}

Integer64 SetHash(Value *setValue) {
    return ValueSetBridge(setValue, NULL)->capacity;
}

void SetEnumerate(Value *setValue, void (*callback)(Value *value)) {
    Set *set = ValueSetBridge(setValue, NULL);
    for (Integer32 index = 0; index < set->capacity; index += 1) {
	Value *value = set->element[index].value;
	if (value != NULL) {
	    callback(value);
	}
    }
}
