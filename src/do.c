#include "do.h"

typedef struct {
    Identifier *name;
    Value *value;
} Statement;

struct Do {
  Integer32 count;
  Statement statements[];
};

static Do *DoCreate(Integer32 count) {
    Do *block = MemoryAllocRegion(sizeof(Do), sizeof(Statement), count);
    block->count = count;
    return block;
}

static void DoDealloc(Do *block) {
    MemoryDealloc(block);
}

Bool DoDecode(Binary *binary, Integer32 *offset, Value **value) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return FALSE;
    Do *block = DoCreate(count);
    for (Integer32 index = 0; index < count; index += 1) {
        Identifier *name;
        Value *value;
        if (!IdentifierDecodePrimitive(binary, offset, &name))
            goto out;
        if (!BinaryDecodeValue(binary, offset, &value))
            goto out;
        block->statements[index].name = name;
        block->statements[index].value = value;
    }
    *value = ValueCreateDo(block);
    return TRUE;

out:
    DoDealloc(block);
    return FALSE;
}

Bool DoExecute(Do *block, Context *context, Stack *stack) {
    Value *value = NULL;
    for (Integer32 index = 0; index < block->count; index += 1) {
        if (!ValueEval(block->statements[index].value, context, stack))
            return FALSE;
        value = StackPopValue(stack);
        Do *executable = ValueDoPrimitive(value);
        if (executable != NULL) {
            if (!DoExecute(executable, context, stack))
                return FALSE;
            value = StackPopValue(stack);
        }
        Identifier *name = block->statements[index].name;
        if (name != NULL)
            ContextSetValueForIdentifier(context, value, name);
    }
    StackReplaceTop(stack, value);
    return TRUE;
}

Bool DoEqual(Do *block, Do *other) {
    if (block->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < block->count; index += 1) {
        if (!IdentifierEqual(block->statements[index].name, other->statements[index].name))
            return FALSE;
        if (!ValueEqual(block->statements[index].value, other->statements[index].value))
            return FALSE;
    }
    return TRUE;
}
