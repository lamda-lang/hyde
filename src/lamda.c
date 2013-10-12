#include "lamda.h"

struct Lamda {
    Integer8 arity;
    Value *result;
    Value *context;
    Value *args[];
};

static Lamda *LamdaCreate(Integer8 arity, Value *result) {
    Lamda *lamda = MemoryAllocRegion(sizeof(Lamda), sizeof(Value *), arity);
    lamda->arity = arity;
    lamda->result = result;
    lamda->context = NULL;
    return lamda;
}

static void LamdaDealloc(Lamda *lamda) {
    MemoryDealloc(lamda);
}

Value *LamdaDecodePrimitive(Binary *binary, Integer32 *offset) {
    Integer8 arity;
    if (!BinaryDecodeInteger8(binary, offset, &arity))
        return NULL;
    Value *result = BinaryDecodeValue(binary, offset);
    if (result == NULL)
        return NULL;
    Lamda *lamda = LamdaCreate(arity, result);
    for (Integer8 index = 0; index < arity; index += 1) {
        Value *arg = BinaryDecodeValue(binary, offset);
        if (arg == NULL)
            goto out;
        lamda->args[index] = arg;
    }
    return ValueCreateLamda(lamda);

out:
    LamdaDealloc(lamda);
    return NULL;
}
