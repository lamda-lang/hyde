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

Bool ListDecode(Binary *binary, Integer32 *offset, Value **value) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return FALSE;
    List *list = ListCreate(count);
    for (Integer32 index = 0; index < count; index += 1) {
        Value *value;
        if (!BinaryDecodeValue(binary, offset, &value))
            goto out;
        list->values[index] = value;
    }
    *value = ValueCreateList(list);
    return TRUE;

out:
    ListDealloc(list);
    return FALSE;
}

Bool ListEval(List *list, Context *context, Stack *stack) {
    List *eval = ListCreate(list->count);
    for (Integer32 index = 0; index < list->count; index += 1) {
        if (!ValueEval(list->values[index], context, stack))
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
