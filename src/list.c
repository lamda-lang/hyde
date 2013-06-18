#include "list.h"

struct List {
    Value base;
    Integer32 count;
    Element element[];
};

List *ListCreate(Integer32 count, Error *error) {
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
Value *ListValueBridge(List *list) {
    return (Value *)list;
}

Value *ListDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    List *list = ListCreate(count, error);
    if (list == NULL) {
	goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
	list->element[index].index = DecodeInteger32VLE(bytes);
    }
    return ListValueBridge(list);

returnError:
    return NULL;
}

void ListFetch(Value *listValue, Value **values) {
    List *list = ValueListBridge(listValue);
    for (Integer32 index = 0; index < list->count; index += 1) {
	Integer32 elementIndex = list->element[index].index;
	list->element[index].value = values[elementIndex];
    }
}

void ListDealloc(Value *listValue) {
    MemoryDealloc(listValue);
}

void ListSetValueAtIndex(List *list, Value *value, Integer32 index) {
    list->element[index].value = value;
}

Value *ListGetValueAtIndex(List *list, Integer32 index) {
    return list->element[index].value;
}

Integer64 ListHash(Value *listValue) {
    return ValueListBridge(listValue)->count;
}

void ListEnumerate(Value *listValue, void (*callback)(Value *value)) {
    List *list = ValueListBridge(listValue);
    for (Integer32 index = 0; index < list->count; index += 1) {
        callback(list->element[index].value);
    }
}

Value *ListEval(Value *listValue, bool pure, Error *error) {
    List *list = ValueListBridge(listValue);
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
