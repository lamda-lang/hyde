#include "list.h"

struct List {
    Value base;
    Integer32 count;
    Element element[];
};

static List *Create(Integer32 count, Error *error) {
    Size size = sizeof(List) + sizeof(Element) * count;
    List *list = MemoryAlloc(size, error);
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
    List *list = Create(count, error);
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
    List *list = ValueListBridge(listValue, NULL);
    Element element[list->count];
    Size size = sizeof(element);
    MemoryCopy(list->element, element, size);
    for (Integer32 index = 0; index < list->count; index += 1) {
	Integer32 elementIndex = element[index].index;
	list->element[index].value = values[elementIndex];
    }
}

void ListDealloc(Value *listValue) {
    MemoryDealloc(listValue);
}

Value *ListGetValueAtIndex(List *list, Integer32 index) {
    return list->element[index].value;
}

Integer64 ListHash(Value *listValue) {
    return ValueListBridge(listValue, NULL)->count;
}

void ListEnumerate(Value *listValue, void (*callback)(Value *value)) {
    List *list = ValueListBridge(listValue, NULL);
    for (Integer32 index = 0; index < list->count; index += 1) {
        callback(list->element[index].value);
    }
}
