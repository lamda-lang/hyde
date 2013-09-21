#include "lamda.h"

struct Lamda {
    Integer8 arity;
    Integer8 count;
    Value *result;
    Value *context;
    Value *args[];
};

static Size LamdaSize(Integer8 count) {
    return sizeof(Lamda) + sizeof(Value *) * count;
}

static Lamda *LamdaCreate(Value *result, Integer8 arity, Integer8 count) {
    Size size = LamdaSize(count);
    Lamda *lamda = MemoryAlloc(size);
    if (lamda == NULL)
        return NULL;
    lamda->arity = arity;
    lamda->count = count;
    lamda->result = result;
    lamda->context = NULL;
    return lamda;
}

Lamda *LamdaDecode(Byte **bytes) {
    Integer8 arity = DecodeInteger8(bytes);
    Value *result = ValueDecode(bytes);
    if (result == NULL)
        return NULL;
    Integer8 count = DecodeInteger8(bytes);
    Lamda *lamda = LamdaCreate(result, arity, count);
    if (lamda == NULL)
        return NULL;
    for (Integer8 index = 0; index < count; index += 1) {
        Value *arg = ValueDecode(bytes);
        if (arg == NULL)
            return LamdaRelease(lamda), NULL;
        lamda->args[index] = arg;
    }
    return lamda;
}

Lamda *LamdaEval(Lamda *lamda, Value *context) {
    Size size = LamdaSize(lamda->count);
    Lamda *new = MemoryClone(lamda, size);
    if (new == NULL)
        return NULL;
    new->context = context;
    return new;
}

Bool LamdaEqual(Lamda *lamda, Lamda *other) {
    if (lamda->arity != other->arity)
        return FALSE;
    if (lamda->count != other->count)
        return FALSE;
    if (!ValueEqual(lamda->result, other->result))
        return FALSE;
    if (!ValueEqual(lamda->context, other->context))
        return FALSE;
    for (Integer8 index = 0; index < lamda->count; index += 1)
        if (!ValueEqual(lamda->args[index], other->args[index]))
            return FALSE;
    return TRUE;
}

Size LamdaRelease(Lamda *lamda) {
    Size size = LamdaSize(lamda->count);
    MemoryDealloc(lamda);
    return size;
}
