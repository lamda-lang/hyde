#include "lamda.h"

struct Lamda {
    Integer8 arity;
    Value *result;
    Value *context;
    Value *args[];
};

static Size LamdaSizeOf(Integer8 count) {
    return sizeof(Lamda) + sizeof(Value *) * count;
}

static Lamda *LamdaCreate(Value *result, Integer8 arity, Error *error) {
    Size size = LamdaSizeOf(arity);
    Lamda *lamda = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    lamda->arity = arity;
    lamda->result = result;
    lamda->context = NULL;
    return lamda;
}

Size LamdaSize(Lamda *lamda) {
    Size size = sizeof(Integer8) + ValueSize(lamda->result) + sizeof(Integer8);
    for (Integer8 index = 0; index < lamda->arity; index += 1)
        size += ValueSize(lamda->args[index]);
    return size;
}

Lamda *LamdaDecode(Byte **bytes, Error *error) {
    Integer8 arity = DecodeInteger8(bytes);
    Value *result = ValueDecode(bytes, error);
    if (ERROR(error))
        return NULL;
    Lamda *lamda = LamdaCreate(result, arity, error);
    if (ERROR(error))
        return NULL;
    for (Integer8 index = 0; index < arity; index += 1) {
        lamda->args[index] = ValueDecode(bytes, error);
        if (ERROR(error))
            goto lamda;
    }
    return lamda;

lamda:
    LamdaRelease(lamda);
    return NULL;
}

Lamda *LamdaEval(Lamda *lamda, Value *context, Error *error) {
    Size size = LamdaSizeOf(lamda->arity);
    Lamda *new = MemoryClone(lamda, size, error);
    if (ERROR(error))
        return NULL;
    new->context = context;
    return new;
}

Bool LamdaEqual(Lamda *lamda, Lamda *other) {
    if (lamda->arity != other->arity)
        return FALSE;
    if (!ValueEqual(lamda->result, other->result))
        return FALSE;
    if (!ValueEqual(lamda->context, other->context))
        return FALSE;
    for (Integer8 index = 0; index < lamda->arity; index += 1)
        if (!ValueEqual(lamda->args[index], other->args[index]))
            return FALSE;
    return TRUE;
}

Size LamdaRelease(Lamda *lamda) {
    Size size = LamdaSizeOf(lamda->arity);
    MemoryDealloc(lamda);
    return size;
}
