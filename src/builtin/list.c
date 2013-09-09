#include <builtin/list.h>

typedef struct List List;

struct List {
    Value value;
    Integer32 count;
    Value *elements[];
};

static List *ListCreate(Integer32 count, Error *error) {
    List *list = MemoryAlloc(sizeof(List) + sizeof(Value *) * count, error);
    if (*error != ErrorNone) return NULL;
    list->value = ValueList;
    list->count = count;
    return list;
}

static List *ListDealloc(List *list) {
    MemoryDealloc(list);
    return NULL;
}

Value *ListDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    List *list = ListCreate(count, error);
    if (*error != ErrorNone) return ListDealloc(list);
    for (Integer32 index = 0; index < count; index += 1) {
        list->elements[index] = DecodeValue(bytes, error);
        if (*error != ErrorNone) return ListDealloc(list);
    }
    return list;
}

Bool ListEqual(Value *listValue, Value *otherValue) {
}

void ListRelease(Value *listValue) {
    ListDealloc(listValue);
}
