#include "lamda.h"

struct Lamda {
    Value base;
    Integer8 arity;
    Integer8 contextLength;
    Byte *code;
    Element context[];
};

static Lamda *Create(Integer8 arity, Integer8 contextLength, Integer32 codeSize, Error *error) {
    Lamda *lamda = MemoryAlloc(sizeof(Lamda) + sizeof(Element) * contextLength, error);
    if (lamda == NULL) {
        goto returnError;
    }
    Byte *code = MemoryAlloc(codeSize, error);
    if (code == NULL) {
        goto deallocLamda;
    }
    lamda->base = TypeLamda;
    lamda->arity = arity;
    lamda->contextLength = contextLength;
    lamda->code = code;
    return lamda;

deallocLamda:
    MemoryDealloc(lamda);
returnError:
    return NULL;
}

void LamdaDealloc(Value *lamdaValue) {
    if (lamdaValue != NULL) {
	Lamda *lamda = BridgeToLamda(lamdaValue);
	MemoryDealloc(lamda->code);
	MemoryDealloc(lamda);
    }
}

Integer64 LamdaHash(Value *lamdaValue) {
    return BridgeToLamda(lamdaValue)->arity;
}

void LamdaEnumerate(Value *lamdaValue, void (*callback)(Value *value)) {
    Lamda *lamda = BridgeToLamda(lamdaValue);
    for (Integer8 index = 0; index < lamda->contextLength; index += 1) {
	Value *value = lamda->context[index].value;
        callback(value);
    }
}

Value *LamdaResult(Value *lamdaValue, Value **args, Integer8 argCount, Error *error) {
    return NULL; /* missing */
}
