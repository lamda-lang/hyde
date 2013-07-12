#include "lamda.h"

typedef struct {
    Integer8 arity;
    Integer8 count;
    Integer32 context[];
} Model;

struct Lamda {
    Value base;
    Integer8 arity;
    Integer8 count;
    Code *code;
    Value *context[];
};

static Lamda *Create(Integer8 arity, Integer8 count, Error *error) {
    Lamda *lamda = MemoryAlloc(sizeof(Lamda) + sizeof(Value *) * count, error);
    if (lamda == NULL) {
        goto returnError;
    }
    lamda->base = TypeLamda;
    lamda->arity = arity;
    lamda->count = count;
    return lamda;

returnError:
    return NULL;
}

void *LamdaDecode(Byte **bytes, Error *error) {
    Integer8 arity = DecodeInteger8FLE(bytes);
    Integer8 count = DecodeInteger8FLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer8) * count, error);
    if (model == NULL) {
        goto returnError;
    }
    model->arity = arity;
    model->count = count;
    for (Integer8 index = 0; index < count; index += 1) {
        model->context[index] = DecodeInteger32VLE(bytes);
    }
    return model;

returnError:
    return NULL;
}

Value *LamdaEval(void *data, Code *code, Value **context, bool pure, Error *error) {
    Model *model = data;
    Lamda *lamda = Create(model->arity, model->count, error);
    if (lamda == NULL) {
        goto returnError;
    }
    Value *lamdaValue = BridgeFromLamda(lamda);
    for (Integer8 index = 0; index < model->count; index += 1) {
        Value *value = CodeEvalInstructionAtIndex(code, context, model->context[index], true, error);
        if (value == NULL) {
            goto deallocLamda;
        }
        lamda->context[index] = value;
    }
    return lamdaValue;
    
deallocLamda:
    LamdaDealloc(lamdaValue);
returnError:
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

Value **LamdaCreateContext(Value *lamdaValue, Error *error) {
    Lamda *lamda = BridgeToLamda(lamdaValue);
    return MemoryAlloc(sizeof(Value *) * (lamda->arity + lamda->count), error);
}

void LamdaDeallocContext(Value **context) {
    MemoryDealloc(context);
}

Value *LamdaResult(Value *lamdaValue, Value **context, Error *error) {
    Lamda *lamda = BridgeToLamda(lamdaValue);
    MemoryCopy(lamda->context, &context[lamda->arity], sizeof(Value *) * lamda->count);
    return CodeEvalInstructionAtIndex(lamda->code, context, 0, true, error);
}
