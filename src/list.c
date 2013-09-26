#include "list.h"

struct List {
    Integer32 count;
    Value *values[];
};

static Size ListSizeOf(Integer32 count) {
    return sizeof(List) + sizeof(Value *) * count;
}

static List *ListCreate(Integer32 count, Error *error) {
    Size size = ListSizeOf(count);
    List *list = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    list->count = count;
    return list;
}

Size ListSize(List *list) {
    Size size = INTEGER_32_SIZE;
    for (Integer32 index = 0; index < list->count; index += 1)
        size += ValueSize(list->values[index]);
    return size;
}

Size ListEncode(List *list, Byte **bytes) {
    EncodeInteger32(list->count, bytes);
    for (Integer32 index = 0; index < list->count; index += 1)
        ValueEncode(list->values[index], bytes);
    return ListSize(list);
}

List *ListDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    List *list = ListCreate(count, error);
    if (ERROR(error))
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        list->values[index] = ValueDecode(bytes, error);
        if (ERROR(error))
            goto list;
    }
    return list;

list:
    ListRelease(list);
    return NULL;
}

List *ListEval(List *list, Value *context, Error *error) {
    List *new = ListCreate(list->count, error);
    if (ERROR(error))
        return NULL;
    for (Integer32 index = 0; index < list->count; index += 1) {
        new->values[index] = ValueEval(list->values[index], context, error);
        if (ERROR(error))
            goto new;
    }
    return new;

new:
    ListRelease(new);
    return NULL;
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
    Size size = ListSizeOf(list->count);
    MemoryDealloc(list);
    return size;
}
