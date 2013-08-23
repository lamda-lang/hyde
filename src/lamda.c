#include "lamda.h"

typedef struct {
    Integer8 arity;
    Integer8 count;
    Integer32 context[];
} Model;

struct Lamda {
    Type  *type;
    Integer8 arity;
    Integer8 count;
    Value *context[];
};

static Lamda *Create(Integer8 arity, Integer8 count, Value **error) {
    Lamda *lamda = MemoryAlloc(sizeof(Lamda) + sizeof(Value *) * count, error);
    if (lamda == NULL) {
        goto returnValue;
    }
    lamda->type = TypeLamda;
    lamda->arity = arity;
    lamda->count = count;
    return lamda;

returnValue:
    return NULL;
}

void *LamdaDecode(Byte **bytes, Value **error) {
    Integer8 arity = DecodeInteger8FLE(bytes);
    Integer8 count = DecodeInteger8FLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer8) * count, error);
    if (model == NULL) {
        goto returnValue;
    }
    model->arity = arity;
    model->count = count;
    for (Integer8 index = 0; index < count; index += 1) {
        model->context[index] = DecodeInteger32VLE(bytes);
    }
    return model;

returnValue:
    return NULL;
}

void LamdaDealloc(Value *lamdaValue) {
    MemoryDealloc(lamdaValue);
}

Integer64 LamdaHash(Value *lamdaValue) {
    return BridgeToLamda(lamdaValue)->arity;
}

Integer8 LamdaArity(Value *lamdaValue) {
    return BridgeToLamda(lamdaValue)->arity;
}

void LamdaEnumerate(Value *lamdaValue, void (*callback)(Value *value)) {
    Lamda *lamda = BridgeToLamda(lamdaValue);
    for (Integer8 index = 0; index < lamda->count; index += 1) {
        callback(lamda->context[index]);
    }
}

Value **LamdaCreateContext(Value *lamdaValue, Value **error) {
    Lamda *lamda = BridgeToLamda(lamdaValue);
    return MemoryAlloc(sizeof(Value *) * (lamda->arity + lamda->count), error);
}

void LamdaDeallocContext(Value **context) {
    MemoryDealloc(context);
}
