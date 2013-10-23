#include "case.h"

typedef struct {
    Value *match;
    Value *guard;
    Value *value;
} Clause;

struct Case {
    Integer32 count;
    Value *arg;
    Clause clauses[];
};

static Case *CaseCreate(Integer32 count, Value *arg) {
    Case *block = MemoryAllocRegion(sizeof(Case), sizeof(Clause), count);
    block->count = count;
    block->arg = arg;
    return block;
}

static void CaseDealloc(Case *block) {
    MemoryDealloc(block);
}

Bool CaseDecode(Binary *binary, Integer32 *offset, Value **value) {
    Integer32 count;
    Value *arg;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return FALSE;
    if (!BinaryDecodeValue(binary, offset, &arg))
        return FALSE;
    Case *block = CaseCreate(count, arg);
    for (Integer32 index = 0; index < count; index += 1) {
        Value *match;
        Value *guard;
        Value *value;
        if (!BinaryDecodeValue(binary, offset, &match))
            goto out;
        if (!BinaryDecodeValue(binary, offset, &guard))
            goto out;
        if (!BinaryDecodeValue(binary, offset, &value))
            goto out;
        block->clauses[index].match = match;
        block->clauses[index].guard = guard;
        block->clauses[index].value = value;
    }
    *value = ValueCreateCase(block);
    return TRUE;

out:
    CaseDealloc(block);
    return FALSE;
}

Bool CaseEval(Case *block, Context *context, Stack *stack) {
    if (!ValueEval(block->arg, context, stack))
        return FALSE;
    Value *arg = StackPopValue(stack);
    for (Integer32 index = 0; index < block->count; index += 1) {
        Clause clause = block->clauses[index];
        if (!ValueEval(clause.match, context, stack))
            return FALSE;
        Value *match = StackPopValue(stack);
        if (!ValueEqual(arg, match))
            continue;
        if (!ValueEval(clause.guard, context, stack))
            return FALSE;
        Value *guard = StackPopValue(stack);
        if (!ValueIsTrue(guard))
            continue;
        if (!ValueEval(clause.value, context, stack))
            return FALSE;
        Value *value = StackPopValue(stack);
        StackReplaceTop(stack, value);
        return TRUE;
    }
    Value *exception = ExceptionCaseClause(arg, stack);
    StackPushValue(stack, exception);
    return FALSE;
}

Bool CaseEqual(Case *block, Case *other) {
    if (block->count != other->count)
        return FALSE;
    if (!ValueEqual(block->arg, other->arg))
        return FALSE;
    for (Integer32 index = 0; index < block->count; index += 1) {
        if (!ValueEqual(block->clauses[index].match, other->clauses[index].match))
            return FALSE;
        if (!ValueEqual(block->clauses[index].guard, other->clauses[index].guard))
            return FALSE;
        if (!ValueEqual(block->clauses[index].value, other->clauses[index].value))
            return FALSE;
    }
    return TRUE;
}
