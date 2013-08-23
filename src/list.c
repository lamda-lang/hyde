#include "list.h"

struct List {
    Type *type;
    Integer32 count;
    VALUE *element[];
};

typedef struct {
    Integer32 count;
    Integer32 index[];
} Model;

static List *Create(Integer32 count, VALUE **error) {
    List *list = MemoryAlloc(sizeof(List) + sizeof(VALUE *) * count, error);
    if (list == NULL) {
        goto returnVALUE;
    }
    list->type = TypeList;
    list->count = count;
    return list;

returnVALUE:
    return NULL;
}

VALUE *ListCreate(Integer32 count, VALUE **error) {
    List *list = Create(count, error);
    return BridgeFromList(list);
}

void *ListDecode(Byte **bytes, VALUE **error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer32) * count, error);
    if (model == NULL) {
        goto returnVALUE;
    }
    model->count = count;
    for (Integer32 index = 0; index < count; index += 1) {
        model->index[index] = DecodeInteger32VLE(bytes);
    }
    return model;

returnVALUE:
    return NULL;
}

void ListDealloc(VALUE *listVALUE) {
    MemoryDealloc(listVALUE);
}

void ListSetVALUEAtIndex(VALUE *listVALUE, VALUE *value, Integer32 index) {
    BridgeToList(listVALUE)->element[index] = value;
}

VALUE *ListGetVALUEAtIndex(VALUE *listVALUE, Integer32 index) {
    return BridgeToList(listVALUE)->element[index];
}

Integer64 ListHash(VALUE *listVALUE) {
    return BridgeToList(listVALUE)->count;
}

void ListEnumerate(VALUE *listVALUE, void (*callback)(VALUE *value)) {
    List *list = BridgeToList(listVALUE);
    for (Integer32 index = 0; index < list->count; index += 1) {
        callback(list->element[index]);
    }
}
