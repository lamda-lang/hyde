#include <builtin/list.h>

typedef struct List List;

struct List {
    Integer32 count;
    Value *elements[];
};

static List *ListCreate(Integer32 count, Error *error) {
    List *list = MemoryAlloc(sizeof(List) + sizeof(Value *) * count, error);
    if (*error != ErrorNone)
        return NULL;
    list->count = count;
    return list;
}

static void ListDealloc(List *list) {
    MemoryDealloc(list);
}

Value *ListDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    List *list = ListCreate(count, error);
    if (*error != ErrorNone)
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        list->elements[index] = DecodeValue(bytes, error);
        if (*error != ErrorNone) {
            ListDealloc(list);
            return NULL;
        }
    }
    return ValueCreate(BuiltinList, list, error);
}

Bool ListEqual(void *listModel, void *otherModel) {
    List *list = listModel;
    List *other = otherModel;
    if (list->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < list->count; index += 1)
        if (!ValueEqual(list->elements[index], other->elements[index]))
            return FALSE;
    return TRUE;
}

void ListRelease(void *listModel) {
    ListDealloc(listModel);
}
