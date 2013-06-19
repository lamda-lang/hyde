#include "list.h"

struct List {
    Value base;
    Integer32 count;
    Element element[];
};

static List *Create(Integer32 count, Error *error) {
    List *list = MemoryAlloc(sizeof(List) + sizeof(Element) * count, error);
    if (list == NULL) {
        goto returnError;
    }
    list->base = TypeList;
    list->count = count;
    return list;

returnError:
    return NULL;
}

Value *ListCreate(Integer32 count, Error *error) {
    List *list = Create(count, error);
    return BridgeFromList(list);
}

Value *ListDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    List *list = Create(count, error);
    if (list == NULL) {
	goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
	list->element[index].index = DecodeInteger32VLE(bytes);
    }
    return BridgeFromList(list);

returnError:
    return NULL;
}

void ListFetch(Value *listValue, Value **values) {
    List *list = BridgeToList(listValue);
    for (Integer32 index = 0; index < list->count; index += 1) {
	Integer32 elementIndex = list->element[index].index;
	list->element[index].value = values[elementIndex];
    }
}

void ListDealloc(Value *listValue) {
    MemoryDealloc(listValue);
}

void ListSetValueAtIndex(Value *listValue, Value *value, Integer32 index) {
    BridgeToList(listValue)->element[index].value = value;
}

Value *ListGetValueAtIndex(Value *listValue, Integer32 index) {
    return BridgeToList(listValue)->element[index].value;
}

Integer64 ListHash(Value *listValue) {
    return BridgeToList(listValue)->count;
}

void ListEnumerate(Value *listValue, void (*callback)(Value *value)) {
    List *list = BridgeToList(listValue);
    for (Integer32 index = 0; index < list->count; index += 1) {
        callback(list->element[index].value);
    }
}

Value *ListEval(Value *listValue, bool pure, Error *error) {
    List *list = BridgeToList(listValue);
    for (Integer32 index = 0; index < list->count; index += 1) {
	Value *before = list->element[index].value;
        Value *after = ValueEval(before, true, error);
	if (after == NULL) {
	    goto returnError;
	}
	list->element[index].value = after;
    }
    return listValue;

returnError:
    return NULL;
}
