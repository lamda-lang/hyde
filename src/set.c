#include "api.h"

struct Set {
    Value base;
    Integer32 length;
    Element *element;
};

static Integer32 IndexForValue(Integer32 length, Value *value, Integer32 offset) {
    return (ValueHash(value) + offset) % length;
}

static void AddValue(Element *element, Integer32 length, Value *value) {
    Integer32 index = IndexForValue(length, value, 0);
    while (element[index].value != NULL) {
	index = IndexForValue(length, value, index);
    }
    element[index].value = value;
}

static Set *Create(Integer32 length, Error *error) {
    Set *set = MemoryAlloc(sizeof(Set), error);
    if (set == NULL) {
        goto returnError;
    }
    Element *element = MemoryAlloc(sizeof(Element) * length, error);
    if (element == NULL) {
	goto deallocSet;
    }
    set->base = TypeSet;
    set->length = length;
    set->element = element;
    return set;

deallocSet:
    MemoryDealloc(set);
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
    return BridgeFromSet(set);

returnError:
    return NULL;
}

void SetFetch(Value *setValue, Byte **values) {
    Set *set = BridgeToSet(setValue);
    for (Integer32 index = 0; index < set->length; index += 1) {
	Integer32 elementIndex = set->element[index].index;
	set->element[index].value = values[elementIndex];
    }
}

void SetDealloc(Value *setValue) {
    if (setValue != NULL) {
	Set *set = BridgeToSet(setValue);
	MemoryDealloc(set->element);
	MemoryDealloc(set);
    }
}

Integer64 SetHash(Value *setValue) {
    return BridgeToSet(setValue)->length;
}

void SetEnumerate(Value *setValue, void (*callback)(Value *value)) {
    Set *set = BridgeToSet(setValue);
    for (Integer32 index = 0; index < set->length; index += 1) {
	Value *value = set->element[index].value;
	if (value != NULL) {
	    callback(value);
	}
    }
}

Value *SetEval(Value *setValue, bool pure, Error *error) {
    Set *set = BridgeToSet(setValue);
    Integer32 length = set->length << 1;
    Element *element = MemoryAlloc(sizeof(Element) * length, error);
    if (element == NULL) {
        goto returnError;
    }
    for (Integer32 index = 0; index < length; index += 1) {
	element[index].value = NULL;
    }
    for (Integer32 index = 0; index < set->length; index += 1) {
	Value *before = set->element[index].value;
	Value *after = ValueEval(before, true, error);
	if (after == NULL) {
	    goto deallocElement;
	}
	AddValue(element, length, after);
    }
    MemoryDealloc(set->element);
    set->length = length;
    set->element = element;
    return setValue;

deallocElement:
    for (Integer32 index = 0; index < length; index += 1) {
	ValueDealloc(element[index].value);
    }
    MemoryDealloc(element);
returnError:
    return NULL;
}
