#include "list.h"

struct List {
    Value base;
    Integer32 count;
    Value *element[];
};

typedef struct {
    Integer32 count;
    Integer32 index[];
} Model;

static List *Create(Integer32 count, Error *error) {
    List *list = MemoryAlloc(sizeof(List) + sizeof(Value *) * count, error);
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

void *ListDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer32) * count, error);
    if (model == NULL) {
        goto returnError;
    }
    model->count = count;
    for (Integer32 index = 0; index < count; index += 1) {
        model->index[index] = DecodeInteger32VLE(bytes);
    }
    return model;

returnError:
    return NULL;
}

Value *ListEval(void *data, Code *code, Value **context, Bool pure, Error *error) {
    Model *model = data;
    List *list = Create(model->count, error);
    if (list == NULL) {
        goto returnError;
    }
    Value *listValue = BridgeFromList(list);
    for (Integer32 index = 0; index < model->count; index += 1) {
        Value *value = CodeEvalInstructionAtIndex(code, context, model->index[index], TRUE, error);
        if (value == NULL) {
            goto deallocList;
        }
        list->element[index] = value;
    }
    return listValue;

deallocList:
    ListDealloc(listValue);
returnError:
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
