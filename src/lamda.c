#include "lamda.h"

struct Lamda {
    Integer8 arity;
    Context *context;
    Value *result;
    Identifier *args[];
};

static Lamda *LamdaCreate(Integer8 arity, Value *result, Context *context) {
    Lamda *lamda = MemoryAllocRegion(sizeof(Lamda), sizeof(Value *), arity);
    lamda->arity = arity;
    lamda->context = context;
    lamda->result = result;
    return lamda;
}

static void LamdaDealloc(Lamda *lamda) {
    MemoryDealloc(lamda);
}

Bool LamdaDecode(Binary *binary, Integer32 *offset, Value **value) {
    Integer8 arity;
    Value *result;
    if (!BinaryDecodeInteger8(binary, offset, &arity))
        return FALSE;
    if (!BinaryDecodeValue(binary, offset, &result))
        return FALSE;
    Lamda *lamda = LamdaCreate(arity, result, NULL);
    for (Integer8 index = 0; index < arity; index += 1) {
        Identifier *arg;
        if (!IdentifierDecodePrimitive(binary, offset, &arg))
            goto out;
        lamda->args[index] = arg;
    }
    *value = ValueCreateLamda(lamda);
    return TRUE;

out:
    LamdaDealloc(lamda);
    return FALSE;
}

Bool LamdaEval(Lamda *lamda, Context *context, Stack *stack) {
    Lamda *eval = LamdaCreate(lamda->arity, lamda->result, context);
    for (Integer8 index = 0; index < lamda->arity; index += 1)
        eval->args[index] = lamda->args[index];
    Value *value = ValueCreateLamda(eval);
    StackReplaceTop(stack, value);
    return TRUE;
}

Bool LamdaEqual(Lamda *lamda, Lamda *other) {
    if (lamda->arity != other->arity)
        return FALSE;
    if (!ContextEqual(lamda->context, other->context))
        return FALSE;
    if (!ValueEqual(lamda->result, other->result))
        return FALSE;
    for (Integer8 index = 0; index < lamda->arity; index += 1)
        if (!IdentifierEqual(lamda->args[index], other->args[index]))
            return FALSE;
    return TRUE;
}
