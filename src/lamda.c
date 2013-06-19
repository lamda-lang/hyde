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

Value *LamdaDecode(Byte **bytes, Error *error) {
    Integer8 arity = DecodeInteger8FLE(bytes);
    Integer8 contextLength = DecodeInteger8FLE(bytes);
    Integer32 codeSize = DecodeInteger32VLE(bytes);
    Lamda *lamda = Create(arity, contextLength, codeSize, error);
    for (Integer8 index = 0; index < contextLength; index += 1) {
	lamda->context[index].index = DecodeInteger32VLE(bytes);
    }
    return BridgeFromLamda(lamda);
}

void LamdaFetch(Value *lamdaValue, Value **values) {
    Lamda *lamda = BridgeToLamda(lamdaValue);
    for (Integer8 index = 0; index < lamda->contextLength; index += 1) {
        Integer32 valueIndex = lamda->context[index].index;
	lamda->context[index].value = values[valueIndex];
    }
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

Value *LamdaEval(Value *lamdaValue, bool pure, Error *error) {
    Lamda *lamda = BridgeToLamda(lamdaValue);
    for (Integer8 index = 0; index < lamda->contextLength; index += 1) {
	Value *value = ValueEval(lamda->context[index].value, true, error);
	if (value == NULL) {
	    goto returnError;
	}
	lamda->context[index].value = value;
    }
    return lamdaValue;

returnError:
    return NULL;
}

Value *LamdaResult(Value *lamdaValue, Value **args, Integer8 argCount, Error *error) {
    Lamda *lamda = BridgeToLamda(lamdaValue);
    return ExecuteCode(lamda->code, args, argCount, &lamda->context[0].value, lamda->contextLength, error);
}
