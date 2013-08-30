#include "list.h"

typedef struct {
    VALUE *type;
    Integer32 count;
    VALUE *elements[];
} List;

static List *ListCreate(Integer32 count, Error *error) {
    List *list = MemoryAlloc(sizeof(List) + sizeof(VALUE *) * count, error);
    if (*error != NULL) {
        return NULL;
    }
    list->type = RuntimeListType;
    list->count = count;
    return list;
}

VALUE *ListDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
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
    return list;

deallocList:
    MemoryDealloc(list);
returnError:
    return NULL;
}

void ListDealloc(VALUE *listValue) {
    MemoryDealloc(listValue);
}
