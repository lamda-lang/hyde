#include "list.h"

struct List {
    Type *type;
    Integer32 count;
    VALUE *elements[];
};

static List *ListCreate(Integer32 count, VALUE **error) {
    List *list = MemoryAlloc(sizeof(List) + sizeof(VALUE *) * count, error);
    if (*error != NULL) {
        return NULL;
    }
    list->type = TypeList;
    list->count = count;
    return list;
}

VALUE *ListDecode(Byte **bytes, VALUE **error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    List *list = ListCreate(count, error);
    if (*error != NULL) {
        goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
        list->elements[index] = DecodeValue(bytes, error);
        if (*error != NULL) {
            goto deallocList;
        }
    }
    return BridgeFromList(list);

deallocList:
    MemoryDealloc(list);
returnError:
    return NULL;
}

void ListDealloc(VALUE *listValue) {
    MemoryDealloc(listValue);
}

Integer64 ListHash(VALUE *listValue) {
    return BridgeToList(listValue)->count;
}
