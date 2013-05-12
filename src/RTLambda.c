#include "RTLambda.h"

enum {
  RTImplementationNative = RTImplementationAlpha,
  RTImplementationForeign = RTImplementationBeta
};

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
  RTByte *buffer = RTMemoryAlloc(codeSize);
  if (lambda == NULL || buffer == NULL) {
    RTMemoryDealloc(lambda);
    RTMemoryDealloc(buffer);
    return NULL;
  }
  lambda->base = RTValueInit(RTTypeLambda, RTImplementationForeign, RTFlagNone);
  lambda->arity = arity;
  lambda->registerCount = registerCount;
  lambda->instructionCount = instructionCount;
  lambda->contextLength = contextLength;
  lambda->codeSize = codeSize;
  lambda->code = buffer;
  RTMemoryCopy(&code, buffer, codeSize);
  *code += codeSize;
  return lambda;
}

void RTLambdaDealloc(RTLambda *lambda) {
  RTMemoryDealloc(lambda->code);
  RTMemoryDealloc(lambda);
}

void RTLambdaSetContextValueAtIndex(RTLambda *lambda, RTValue *value, RTInteger32Bit index) {
  lambda->context[index] = value;
}

RTInteger64Bit RTLambdaHash(RTLambda *lambda) {
  return lambda->registerCount;
}

bool RTLambdaEqual(RTLambda *lambda, RTLambda *other) {
  if (lambda->arity != other->arity ||
      lambda->registerCount != other->registerCount ||
      lambda->instructionCount != other->instructionCount || 
      lambda->contextLength != other->contextLength ||
      !RTMemoryEqual(lambda->code, other->code, lambda->codeSize)) {
    return false;
  }
  for (RTInteger32Bit index = 0; index < lambda->contextLength; index += 1) {
    /* missing */
  }
  return true;
}

RTInteger32Bit RTLambdaRegisterCount(RTLambda *lambda) {
  return lambda->registerCount;
}

RTError RTLambdaExecute(RTLambda *lambda, RTStack *stack, RTInteger8Bit arity) {
  /* missing */
  lambda = NULL;
  stack = NULL;
  arity = 0;
  return RTErrorNone;
}

void RTLambdaEnumerateContext(RTLambda *lambda, RTBlock *block) {
  for (RTInteger32Bit index = 0; index < lambda->contextLength; index += 1) {
    block(lambda->context[index]);
  }
}
