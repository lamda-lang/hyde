#include "RTLambda.h"

struct RTLambda {
  RTBase base;
  RTInteger8Bit arity;
  RTInteger32Bit length;
  RTInteger32Bit count;
  RTByte *code;
  RTValue context[];
};

static inline RTBool EqualMembers(RTLambda lambda, RTLambda other) {
  return lambda->length == other->length && lambda->count == other->count && lambda->arity == other->arity;
}

RTValue RTLambdaValueBridge(RTLambda lambda) {
  return (RTValue)lambda;
}

RTLambda RTLambdaCreate(RTByte *code, RTInteger32Bit length, RTInteger8Bit arity, RTInteger32Bit count) {
  RTSize size = sizeof(struct RTLambda) + sizeof(RTValue) * count;
  RTLambda lambda = RTMemoryAlloc(size);
  RTByte *buffer = RTMemoryAlloc(length);
  if (lambda == NULL || buffer == NULL) {
    RTMemoryDealloc(lambda);
    RTMemoryDealloc(buffer);
    return NULL;
  }
  RTMemoryCopy(code, buffer, length);
  lambda->base = RTBaseInit(RTTypeLambda, RTFlagNone);
  lambda->code = buffer;
  lambda->length = length;
  lambda->count = count;
  lambda->arity = arity;
  return lambda;
}

void RTLambdaDealloc(RTLambda lambda) {
  RTMemoryDealloc(lambda->code);
  RTMemoryDealloc(lambda);
}

void RTLambdaSetContextValueAtIndex(RTLambda lambda, RTValue value, RTInteger32Bit index) {
  lambda->context[index] = value;
}

RTInteger64Bit RTLambdaHash(RTLambda lambda) {
  return lambda->length;
}

RTBool RTLambdaEqual(RTLambda lambda, RTLambda other) {
  if (EqualMembers(lambda, other) == FALSE || RTMemoryCompare(lambda->code, other->code, lambda->length)) {
    return FALSE;
  }
  for (RTInteger32Bit index = 0; index < lambda->count; index += 1) {
    if (RTValueEqual(lambda->context[index], other->context[index]) == FALSE) {
      return FALSE;
    }
  }
  return TRUE;
}

RTValue RTLambdaExecute(RTLambda lambda, RTValue *arg, RTInteger8Bit count) {
  lambda = NULL;
  arg = NULL;
  count = 0;
  return NULL;
}

void RTLambdaEnumerateContext(RTLambda lambda, RTBlock block) {
  for (RTInteger32Bit index = 0; index < lambda->count; index += 1) {
    block(lambda->context[index]);
  }
}
