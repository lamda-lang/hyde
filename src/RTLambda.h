#ifndef RT_LAMBDA
#define RT_LAMBDA

#include "Runtime.h"

RTLambda RTLambdaCreate(RTByte *code, RTInteger32Bit length, RTInteger8Bit arity, RTInteger32Bit count);

void RTLambdaDealloc(RTLambda lambda);

void RTLambdaSetContextValueAtIndex(RTLambda lambda, RTValue value, RTInteger32Bit index);

RTInteger64Bit RTLambdaHash(RTLambda lambda);

RTBool RTLambdaEqual(RTLambda lambda, RTLambda other);

RTValue RTLambdaExecute(RTLambda lambda, RTValue *arg);

#endif
