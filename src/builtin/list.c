#include <builtin/list.h>

typedef struct List List;

struct List {
    VALUE *type;
    Integer32 count;
    VALUE *elements[];
};

static List *ListCreate(Integer32 count, Error *error) {
    List *list = MemoryAlloc(sizeof(List) + sizeof(VALUE *) * count, error);
    if (*error != ErrorNone) return NULL;
    list->type = RuntimeValueForConstant(ConstantListType);
    list->count = count;
    return list;
}

VALUE *ListDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    List *list = ListCreate(count, error);
    if (*error != ErrorNone) goto returnError;
    for (Integer32 index = 0; index < count; index += 1) {
        list->elements[index] = DecodeValue(bytes, error);
        if (*error != ErrorNone) goto deallocList;
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
