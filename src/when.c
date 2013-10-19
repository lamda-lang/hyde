#include "when.h"

typedef struct {
    Value *condition;
    Value *value;
} Clause;

struct When {
    Integer32 count;
    Clause clauses[];
}; 

static When *WhenCreate(Integer32 count) {
    When *block = MemoryAllocRegion(sizeof(When), sizeof(Clause), count);
    block->count = count;
    return block;
}

static void WhenDealloc(When *block) {
    MemoryDealloc(block);
}

Bool WhenDecode(Binary *binary, Integer32 *offset, Value **value) {
    Integer32 count;
    Value *arg;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return FALSE;
    if (!BinaryDecodeValue(binary, offset, &arg))
        return FALSE;
    When *block = WhenCreate(count);
    for (Integer32 index = 0; index < count; index += 1) {
        Value *condition;
        Value *value;
        if (!BinaryDecodeValue(binary, offset, &condition))
            goto out;
        if (!BinaryDecodeValue(binary, offset, &value))
            goto out;
        block->clauses[index].condition = condition;
        block->clauses[index].value = value;
    }
    *value = ValueCreateWhen(block);
    return TRUE;

out:
    WhenDealloc(block);
    return FALSE;
}

Bool WhenEval(When *block, Context *context, Stack *stack) {
    for (Integer32 index = 0; index < block->count; index += 1) {
        if (!ValueEval(block->clauses[index].condition, context, stack))
            return FALSE;
        Value *condition = StackPopValue(stack);
        if (ValueIsTrue(condition))
            return ValueEval(block->clauses[index].value, context, stack);
    }
    Value *exception = ExceptionWhenClause(stack);
    StackPushValue(stack, exception);
    return FALSE;
}
