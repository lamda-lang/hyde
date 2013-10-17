#include "list.h"

struct List {
    Integer32 count;
    Value *values[];
};

static List *ListCreate(Integer32 count) {
    List *list = MemoryAllocRegion(sizeof(List), sizeof(Value *), count);
    list->count = count;
    return list;
}

static void ListDealloc(List *list) {
    MemoryDealloc(list);
}

Value *ListDecode(Binary *binary, Integer32 *offset) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return NULL;
    List *list = ListCreate(count);
    for (Integer32 index = 0; index < count; index += 1) {
        Value *value = BinaryDecodeValue(binary, offset);
        if (value == NULL)
            goto out;
        list->values[index] = value;
    }
    return ValueCreateList(list);

out:
    ListDealloc(list);
    return NULL;
}

Bool ListEval(List *list, Stack *stack) {
    List *eval = ListCreate(list->count);
    for (Integer32 index = 0; index < list->count; index += 1) {
        if (!ValueEval(list->values[index], stack))
            goto out;
        eval->values[index] = StackPopValue(stack);
    }
    Value *value = ValueCreateList(eval);
    StackReplaceTop(stack, value);
    return TRUE;

out:
    ListDealloc(eval);
    return FALSE;
}
