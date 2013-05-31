#include "lambda.h"

struct Lambda {
    Value base;
    Integer8 arity;
    Integer8 contextLength;
    Integer32 registerCount;
    Integer32 instructionCount;
    Byte *code;
    Value *context[];
};

Lambda *LambdaDecode(Byte **bytes, Error *error) {
    Integer32 registerCount = DecodeInteger32VLE(bytes);
    Integer32 instructionCount = DecodeInteger32VLE(bytes);
    Integer8 contextLength = DecodeInteger8FLE(bytes);
    Integer32 codeSize = DecodeInteger32VLE(bytes);
    Integer8 arity = DecodeInteger8FLE(bytes);
    Size size = sizeof(Lambda) + sizeof(Value) * contextLength;
    Lambda *lambda = MemoryAlloc(size, error);
    if (lambda == NULL) {
        goto returnError;
    }
    Byte *code = MemoryAlloc(codeSize, error);
    if (code == NULL) {
        goto deallocLambda;
    }
    MemoryCopy(*bytes, code, codeSize);
    *bytes += codeSize;
    lambda->base = TypeLambda;
    lambda->arity = arity;
    lambda->registerCount = registerCount;
    lambda->instructionCount = instructionCount;
    lambda->contextLength = contextLength;
    lambda->code = code;
    return lambda;

deallocLambda:
  MemoryDealloc(lambda);
returnError:
  return NULL;
}

Value *LambdaValueBridge(Lambda *lambda) {
    return (Value *)lambda;
}

void LambdaDealloc(Value *lambdaValue) {
    Lambda *lambda = ValueLambdaBridge(lambdaValue);
    MemoryDealloc(lambda->code);
    MemoryDealloc(lambda);
}

void LambdaFetch(Lambda *lambda, Value **values, Byte **bytes) {
    for (Integer8 index = 0; index < lambda->contextLength; index += 1) {
	Integer32 contextIndex = DecodeInteger32VLE(bytes);
	lambda->context[index] = values[contextIndex];
    }
}

Integer64 LambdaHash(Value *lambdaValue) {
    Lambda *lambda = ValueLambdaBridge(lambdaValue);
    return lambda->registerCount;
}

Integer32 LambdaRegisterCount(Lambda *lambda) {
    return lambda->registerCount;
}

Status LambdaExecute(Lambda *lambda, Stack *stack, Integer8 arity, Error *error) {
    if (arity != lambda->arity) {
	*error = ErrorArityMismatch;
        goto returnError;
    }
    return ExecuteCode(lambda->code, lambda->instructionCount, stack, error);

returnError:
    return StatusFailure;
}

void LambdaEnumerate(Value *lambdaValue, void (*block)(Value *value)) {
    Lambda *lambda = ValueLambdaBridge(lambdaValue);
    for (Integer32 index = 0; index < lambda->contextLength; index += 1) {
        block(lambda->context[index]);
    }
}
