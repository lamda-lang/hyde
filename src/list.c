#include "list.h"

struct List {
    Type *type;
    Integer32 count;
    Value *element[];
};

typedef struct {
    Integer32 count;
    Integer32 index[];
} Model;

static List *Create(Integer32 count, Value **error) {
    List *list = MemoryAlloc(sizeof(List) + sizeof(Value *) * count, error);
    if (list == NULL) {
        goto returnValue;
    }
    list->type = TypeList;
    list->count = count;
    return list;

returnValue:
    return NULL;
}

Value *ListCreate(Integer32 count, Value **error) {
    List *list = Create(count, error);
    return BridgeFromList(list);
}

void *ListDecode(Byte **bytes, Value **error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer32) * count, error);
    if (model == NULL) {
        goto returnValue;
    }
    model->count = count;
    for (Integer32 index = 0; index < count; index += 1) {
        model->index[index] = DecodeInteger32VLE(bytes);
    }
    return model;

returnValue:
    return NULL;
}

void ListDealloc(Value *listValue) {
    MemoryDealloc(listValue);
}

void ListSetValueAtIndex(Value *listValue, Value *value, Integer32 index) {
    BridgeToList(listValue)->element[index] = value;
}

Value *ListGetValueAtIndex(Value *listValue, Integer32 index) {
    return BridgeToList(listValue)->element[index];
}

Integer64 ListHash(Value *listValue) {
    return BridgeToList(listValue)->count;
}

void ListEnumerate(Value *listValue, void (*callback)(Value *value)) {
    List *list = BridgeToList(listValue);
    for (Integer32 index = 0; index < list->count; index += 1) {
        callback(list->element[index]);
    }
}
