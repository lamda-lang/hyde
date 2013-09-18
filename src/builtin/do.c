#include <builtin/do.h>

typedef struct Statement Statement;

struct Statement {
    Value *name;
    Value *value;
};

struct Do {
  Integer32 count;
  Statement statements[];
};

static Size DoSize(Integer32 count) {
    return sizeof(Do) * sizeof(Statement) * count;
}

static Do *DoCreate(Integer32 count) {
    Size size = DoSize(count);
    Do *block = MemoryAlloc(size);
    if (block == NULL)
        return NULL;
    block->count = count;
    return block;
}

Do *DoDecode(Byte **bytes) {
    Integer32 count = DecodeInteger32(bytes);
    Do *block = DoCreate(count);
    if (block == NULL)
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        Value *name = ValueDecode(bytes);
        if (name == NULL)
            return DoRelease(block), NULL;
        Value *value = ValueDecode(bytes);
        if (value == NULL)
            return DoRelease(block), NULL;
        block->statements[index].name = name;
        block->statements[index].value = value;
    }
    return block;
}

Value *DoEval(Do *block, Value *context) {
    Value *value = NULL;
    for (Integer32 index = 0; index < block->count; index += 1) {
        value = ValueEval(block->statements[index].value, context);
        if (value == NULL)
            return NULL;
        if (block->statements[index].name != VALUE_NIL)
            context = ValueSetValueForKey(context, value, block->statements[index].name);
    }
    return value;
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
    Size size = DoSize(block->count);
    MemoryDealloc(block);
    return size;
}
