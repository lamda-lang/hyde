#include "do.h"

typedef struct Statement Statement;

struct Statement {
    Value *name;
    Value *value;
};

struct Do {
  Integer32 count;
  Statement statements[];
};

static Size DoSizeOf(Integer32 count) {
    return sizeof(Do) * sizeof(Statement) * count;
}

static Do *DoCreate(Integer32 count, Error *error) {
    Size size = DoSizeOf(count);
    Do *block = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    block->count = count;
    return block;
}

Size DoSize(Do *block) {
    Size size = INTEGER_32_SIZE;
    for (Integer32 index = 0; index < block->count; index += 1) {
        size += ValueSize(block->statements[index].name);
        size += ValueSize(block->statements[index].value);
    }
    return size;
}

Size DoEncode(Do *block, Byte **bytes) {
    EncodeInteger32(block->count, bytes);
    for (Integer32 index = 0; index < block->count; index += 1) {
        ValueEncode(block->statements[index].name, bytes);
        ValueEncode(block->statements[index].value, bytes);
    }
    return DoSize(block);
}

Do *DoDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Do *block = DoCreate(count, error);
    if (ERROR(error))
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        block->statements[index].name = ValueDecode(bytes, error);
        if (ERROR(error))
            goto block;
        block->statements[index].value = ValueDecode(bytes, error);
        if (ERROR(error))
            goto block;
    }
    return block;

block:
    DoRelease(block);
    return NULL;
}

Value *DoEval(Value *value, Do *block, Value *context, Error *error) {
    Value *result = NULL;
    for (Integer32 index = 0; index < block->count; index += 1) {
        result = ValueEval(block->statements[index].value, context, error);
        if (ERROR(error))
            return NULL;
        if (!ValueIsNil(block->statements[index].name))
            context = ValueSetValueForKey(context, result, block->statements[index].name, error);
        if (result == NULL)
            return NULL;
    }
    return result;
}

Bool DoEqual(Do *block, Do *other) {
    if (block->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < block->count; index += 1) {
        if (!ValueEqual(block->statements[index].name, other->statements[index].name))
            return FALSE;
        if (!ValueEqual(block->statements[index].value, other->statements[index].value))
            return FALSE;
    }
    return TRUE;
}

Size DoRelease(Do *block) {
    Size size = DoSizeOf(block->count);
    MemoryDealloc(block);
    return size;
}
