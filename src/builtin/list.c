#include <builtin/list.h>

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

Value *ListDecode(Byte **bytes) {
    Integer32 count = DecodeInteger32(bytes);
    List *list = ListCreate(count);
    if (list == NULL)
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        Value *value = ValueDecode(bytes);
        if (value == NULL)
            return ListRelease(list), NULL;
        list->values[index] = value;
    }
    return ValueCreate(MODEL_LIST, list);
}

Bool ListEqual(List *list, List *other) {
    if (list->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < list->count; index += 1)
        if (!ValueEqual(list->values[index], other->values[index]))
            return FALSE;
    return TRUE;
}

Size ListRelease(List *list) {
    Integer32 count = list->count;
    MemoryDealloc(list);
    return sizeof(List) + sizeof(Value *) * count;
}
