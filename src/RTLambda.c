#include "RTLambda.h"

struct RTLambda {
  RTValue base;
  RTInteger8Bit arity;
  RTInteger32Bit registerCount;
  RTInteger32Bit instructionCount;
  RTInteger32Bit contextLength;
  RTInteger32Bit codeSize;
  RTByte *code;
  RTValue *context[];
};

RTValue *RTLambdaValueBridge(RTLambda *lambda) {
  return (RTValue *)lambda;
}

RTLambda *RTLambdaDecode(RTByte **code) {
  RTInteger32Bit registerCount = RTDecodeVBRInteger32Bit(code);
  RTInteger32Bit instructionCount = RTDecodeVBRInteger32Bit(code);
  RTInteger32Bit contextLength = RTDecodeVBRInteger32Bit(code);
  RTInteger32Bit codeSize = RTDecodeVBRInteger32Bit(code);
  RTInteger8Bit arity = RTDecodeInteger8Bit(code);
  RTSize size = sizeof(struct RTLambda) + sizeof(RTValue) * contextLength;
  RTLambda *lambda = RTMemoryAlloc(size);
  if (lambda == NULL) {
    goto error;
  }
  RTByte *buffer = RTMemoryAlloc(codeSize);
  if (buffer == NULL) {
    goto errorBuffer;
  }
  lambda->base = RTValueInit(RTTypeLambda, RTFlagNone);
  lambda->arity = arity;
  lambda->registerCount = registerCount;
  lambda->instructionCount = instructionCount;
  lambda->contextLength = contextLength;
  lambda->codeSize = codeSize;
  lambda->code = buffer;
  RTMemoryCopy(&code, buffer, codeSize);
  *code += codeSize;
  return lambda;

errorBuffer:
  RTMemoryDealloc(lambda);
error:
  return NULL;
}

void RTLambdaDealloc(RTValue *lambda_RTLambda) {
  RTLambda *lambda = RTValueLambdaBridge(lambda_RTLambda);
  RTMemoryDealloc(lambda->code);
  RTMemoryDealloc(lambda);
}

void RTLambdaSetContextValueAtIndex(RTLambda *lambda, RTValue *value, RTInteger32Bit index) {
  lambda->context[index] = value;
}

RTInteger64Bit RTLambdaHash(RTValue *lambda_RTLambda) {
  RTLambda *lambda = RTValueLambdaBridge(lambda_RTLambda);
  return lambda->registerCount;
}

RTInteger32Bit RTLambdaRegisterCount(RTLambda *lambda) {
  return lambda->registerCount;
}

RTStatus RTLambdaExecute(RTLambda *lambda, RTStack *stack, RTInteger8Bit arity) {
  if (arity != lambda->arity) {
    goto error;
  }
  return RTExecuteCode(lambda->code, lambda->instructionCount, stack);

error:
  return RTStatusFailure;
}

void RTLambdaEnumerate(RTValue *lambda_RTLambda, RTBlock *block) {
  RTLambda *lambda = RTValueLambdaBridge(lambda_RTLambda);
  for (RTInteger32Bit index = 0; index < lambda->contextLength; index += 1) {
    block(lambda->context[index]);
  }
}
