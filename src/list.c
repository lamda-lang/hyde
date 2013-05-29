#include "list.h"

struct List {
    Value base;
    Integer32 length;
    Value *element[];
};

static inline List *Create(Integer32 length, Error *error) {
    Size size = sizeof(List) + sizeof(Value) * length;
    List *list = MemoryAlloc(size, error);
    if (list == NULL) {
        goto returnError;
    }
    list->base = TypeList;
    list->length = length;
    return list;

returnError:
    return NULL;
}

Value *ListValueBridge(List *list) {
    return (Value *)list;
}

List *ListDecode(Byte **bytes, Error *error) {
    Integer32 length = DecodeInteger32VLE(bytes);
    return Create(length, error);
}

void ListDealloc(Value *listValue) {
    MemoryDealloc(listValue);
}

void ListSetValueAtIndex(List *list, Value *value, Integer32 index) {
    list->element[index] = value;
}

Value *ListGetValueAtIndex(List *list, Integer32 index) {
    return list->element[index];
}

Integer64 ListHash(Value *listValue) {
    List *list = ValueListBridge(listValue);
    return list->length;
}

void ListEnumerate(Value *listValue, void (*block)(Value *value)) {
    List *list = ValueListBridge(listValue);
    for (Integer32 index = 0; index < list->length; index += 1) {
        block(list->element[index]);
    }
}
