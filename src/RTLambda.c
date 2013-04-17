#include "RTLambda.h"

struct RTLambda {
  RTByte *code;
  RTInteger32Bit length;
  RTInteger32Bit count;
  RTInteger8Bit arity;
  RTValue context[];
};

static inline RTBool EqualMembers(RTLambda lambda, RTLambda other) {
  return lambda->length == other->length && lambda->count == other->count && lambda->arity == other->arity;
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

RTValue RTLambdaExecute(RTLambda lambda, RTValue *arg) {
  return RTExecuteCode(lambda->code, arg, lambda->arity);
}
