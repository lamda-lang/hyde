#include "lambda.h"

struct Lambda {
    Value base;
    Integer8 arity;
    Integer32 registerCount;
    Integer32 instructionCount;
    Integer32 contextLength;
    Byte *code;
    Value *context[];
};

Lambda *LambdaDecode(Byte **bytes, Exception *exception) {
    Integer32 registerCount = DecodeInteger32VLE(bytes);
    Integer32 instructionCount = DecodeInteger32VLE(bytes);
    Integer32 contextLength = DecodeInteger32VLE(bytes);
    Integer32 codeSize = DecodeInteger32VLE(bytes);
    Integer8 arity = DecodeInteger8FLE(bytes);
    Size size = sizeof(Lambda) + sizeof(Value) * contextLength;
    Lambda *lambda = MemoryAlloc(size, exception);
    if (lambda == NULL) {
        goto returnError;
    }
    Byte *code = MemoryAlloc(codeSize, exception);
    if (code == NULL) {
        goto deallocLambda;
    }
    lambda->base = TypeLambda;
    lambda->arity = arity;
    lambda->registerCount = registerCount;
    lambda->instructionCount = instructionCount;
    lambda->contextLength = contextLength;
    lambda->code = code;
    MemoryCopy(*bytes, lambda->code, codeSize);
    *code += codeSize;
    return lambda;

deallocLambda:
  MemoryDealloc(lambda);
returnError:
  return NULL;
}

Value *LambdaValueBridge(Lambda *lambda) {
    return (Value *)lambda;
}

void LambdaDealloc(Value *lambda) {
    Lambda *lambdaBridge = ValueLambdaBridge(lambda);
    MemoryDealloc(lambdaBridge->code);
    MemoryDealloc(lambdaBridge);
}

void LambdaSetContextValueAtIndex(Lambda *lambda, Value *value, Integer32 index) {
    lambda->context[index] = value;
}

Integer64 LambdaHash(Value *lambda) {
    Lambda *lambdaBridge = ValueLambdaBridge(lambda);
    return lambdaBridge->registerCount;
}

Integer32 LambdaRegisterCount(Lambda *lambda) {
    return lambda->registerCount;
}

Status LambdaExecute(Lambda *lambda, Stack *stack, Integer8 arity, Exception *exception) {
    if (arity != lambda->arity) {
	ExceptionRaise(exception, ErrorArityMismatch);
        goto returnError;
    }
    return ExecuteCode(lambda->code, lambda->instructionCount, stack, exception);

returnError:
    return StatusFailure;
}

void LambdaEnumerate(Value *lambda, void (*block)(Value *value)) {
    Lambda *lambdaBridge = ValueLambdaBridge(lambda);
    for (Integer32 index = 0; index < lambdaBridge->contextLength; index += 1) {
        block(lambdaBridge->context[index]);
    }
}
