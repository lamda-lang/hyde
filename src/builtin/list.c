#include <builtin/list.h>

typedef struct List List;

struct List {
    Integer32 count;
    Value *values[];
};

static List *ListCreate(Integer32 count) {
    List *list = MemoryAlloc(sizeof(List) + sizeof(Value *) * count);
    if (list == NULL)
        return NULL;
    list->count = count;
    return list;
}

Value *ListDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    List *list = ListCreate(count);
    if (list == NULL)
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        Value *value = DecodeValue(bytes, error);
        if (value == NULL)
            return ListRelease(list), NULL;
        list->values[index] = value;
    }
    return ValueCreate(ModelList, list);
}

Bool ListEqual(void *listData, void *otherData) {
    List *list = listData;
    List *other = otherData;
    if (list->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < list->count; index += 1)
        if (!ValueEqual(list->values[index], other->values[index]))
            return FALSE;
    return TRUE;
}

void ListRelease(void *listData) {
    MemoryDealloc(listData);
}
