#include "lambda.h"

struct Args {
    Integer8 count;
    Value *value[];
};

struct Lambda {
    Value base;
    Integer8 arity;
    Integer8 contextLength;
    Integer32 registerCount;
    Integer32 instructionCount;
    Byte *code;
    Value *context[];
};

static void DeallocArgs(Args *args) {
    MemoryDealloc(args);
}

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
    Lambda *lambda = ValueLambdaBridge(lambdaValue, NULL);
    MemoryDealloc(lambda->code);
    MemoryDealloc(lambda);
}

void LambdaSetContextValueAtIndex(Lambda *lambda, Value *value, Integer8 index) {
    lambda->context[index] = value;
}

Integer8 LambdaContextLength(Lambda *lambda) {
    return lambda->contextLength;
}

Integer64 LambdaHash(Value *lambdaValue) {
    Lambda *lambda = ValueLambdaBridge(lambdaValue, NULL);
    return lambda->registerCount;
}

Value *LambdaExecute(Lambda *lambda, Args *args, Stack *stack, Error *error) {
    if (args->count != lambda->arity) {
	*error = ErrorArityMismatch;
	goto returnError;
    }
    if (StackPushFrame(stack, lambda->registerCount, error) == StatusFailure) {
	goto returnError;
    }
    for (Integer8 index = 0; index < args->count; index += 1) {
	StackFrameArgs(stack)[index] = args->value[index];
    }
    if (ExecuteCode(lambda->code, lambda->instructionCount, stack, error) == StatusFailure) {
	goto pullFrame;
    }
    Value *result = *StackFrameResult(stack);
    StackPullFrame(stack);
    DeallocArgs(args);
    return result;

pullFrame:
    StackPullFrame(stack);
returnError:
    return NULL;
}

void LambdaEnumerate(Value *lambdaValue, void (*block)(Value *value)) {
    Lambda *lambda = ValueLambdaBridge(lambdaValue, NULL);
    for (Integer32 index = 0; index < lambda->contextLength; index += 1) {
        block(lambda->context[index]);
    }
}

Args *ArgsDecode(Byte **bytes, Error *error) {
    Integer8 count = DecodeInteger8FLE(bytes);
    Size size = sizeof(Args) + sizeof(Value *) * count;
    Args *args = MemoryAlloc(size, error);
    if (args == NULL) {
	goto returnError;
    }
    args->count = count;
    return args;

returnError:
    return NULL;
}

Integer8 ArgsCount(Args *args) {
    return args->count;
}

Value **ArgsValues(Args *args) {
    return args->value;
}

