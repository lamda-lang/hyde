#include "lambda.h"

struct Lambda {
    Value base;
    Integer8 arity;
    Integer8 contextLength;
    Integer32 valueCount;
    Byte *code;
    Element context[];
};

static Lambda *Create(Integer8 arity, Integer8 contextLength, Integer32 valueCount, Integer32 codeSize, Error *error) {
    Size size = sizeof(Lambda) + sizeof(Element) * contextLength;
    Lambda *lambda = MemoryAlloc(size, error);
    if (lambda == NULL) {
        goto returnError;
    }
    Byte *code = MemoryAlloc(codeSize, error);
    if (code == NULL) {
        goto deallocLambda;
    }
    lambda->base = TypeLambda;
    lambda->arity = arity;
    lambda->contextLength = contextLength;
    lambda->valueCount = valueCount;
    lambda->code = code;
    return lambda;

deallocLambda:
    MemoryDealloc(lambda);
returnError:
    return NULL;
}

Value *LambdaDecode(Byte **bytes, Error *error) {
    Integer8 arity = DecodeInteger8FLE(bytes);
    Integer8 contextLength = DecodeInteger8FLE(bytes);
    Integer32 valueCount = DecodeInteger32VLE(bytes);
    Integer32 codeSize = DecodeInteger32VLE(bytes);
    Lambda *lambda = Create(arity, contextLength, valueCount, codeSize, error);
    for (Integer8 index = 0; index < contextLength; index += 1) {
	lambda->context[index].index = DecodeInteger32VLE(bytes);
    }
    return LambdaValueBridge(lambda);
}

void LambdaFetch(Value *lambdaValue, Value **values) {
    Lambda *lambda = ValueLambdaBridge(lambdaValue);
    for (Integer8 index = 0; index < lambda->contextLength; index += 1) {
        Integer32 valueIndex = lambda->context[index].index;
	lambda->context[index].value = values[valueIndex];
    }
}

Value *LambdaValueBridge(Lambda *lambda) {
    return (Value *)lambda;
}

void LambdaDealloc(Value *lambdaValue) {
    Lambda *lambda = ValueLambdaBridge(lambdaValue);
    MemoryDealloc(lambda->code);
    MemoryDealloc(lambda);
}

Integer64 LambdaHash(Value *lambdaValue) {
    return ValueLambdaBridge(lambdaValue)->valueCount;
}

void LambdaEnumerate(Value *lambdaValue, void (*callback)(Value *value)) {
    Lambda *lambda = ValueLambdaBridge(lambdaValue);
    for (Integer8 index = 0; index < lambda->contextLength; index += 1) {
	Value *value = lambda->context[index].value;
        callback(value);
    }
}

Value *LambdaEval(Value *lambdaValue, Error *error) {
    Lambda *lambda = ValueLambdaBridge(lambdaValue);
    for (Integer8 index = 0; index < lambda->contextLength; index += 1) {
	Value *value = ValueEval(lambda->context[index].value, error);
	if (value == NULL) {
	    goto returnError;
	}
	lambda->context[index].value = value;
    }
    return lambdaValue;

returnError:
    return NULL;
}

Value *LambdaResult(Lambda *lambda, Value **args, Integer8 argCount, Error *error) {
    return NULL;
}
