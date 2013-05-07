#ifndef RT_LAMBDA
#define RT_LAMBDA

#include "Runtime.h"

RTValue RTLambdaValueBridge(RTLambda lambda);

RTLambda RTLambdaDecode(RTByte **code);

void RTLambdaDealloc(RTLambda lambda);

void RTLambdaSetContextValueAtIndex(RTLambda lambda, RTValue value, RTInteger32Bit index);

RTInteger64Bit RTLambdaHash(RTLambda lambda);

RTBool RTLambdaEqual(RTLambda lambda, RTLambda other);

RTValue RTLambdaExecute(RTLambda lambda, RTValue *arg, RTInteger8Bit count);

void RTLambdaEnumerateContext(RTLambda lambda, RTBlock block);

#endif
