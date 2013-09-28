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
    Size size = ValueSize(lamda->result) + INTEGER_8_SIZE;
    for (Integer8 index = 0; index < lamda->arity; index += 1)
        size += ValueSize(lamda->args[index]);
    return size;
}

Size LamdaEncode(Lamda *lamda, Byte **bytes) {
    EncodeInteger8(lamda->arity, bytes);
    ValueEncode(lamda->result, bytes);
    for (Integer8 index = 0; index < lamda->arity; index += 1)
        ValueEncode(lamda->args[index], bytes);
    return LamdaSize(lamda);
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

Value *LamdaEval(Value *value, Lamda *lamda, Value *context, Error *error) {
    Size size = LamdaSizeOf(lamda->arity);
    Lamda *new = MemoryClone(lamda, size, error);
    if (ERROR(error))
        return NULL;
    new->context = context;
    return ValueCopy(new, error);
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

Value *LamdaCall(Lamda *lamda, Value **args, Integer8 count, Error *error) {
    if (count != lamda->arity)
        goto error;
    Value *context = lamda->context;
    for (Integer8 index = 0; index < count; index += 1) {
        context = ValueSetValueForKey(context, args[index], lamda->args[index], error);
        if (ERROR(error))
            return NULL;
    }
    return ValueEval(lamda->result, context, error);

error:
    *error = ERROR_INVALID_ARITY;
    return NULL;
}
