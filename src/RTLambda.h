#ifndef RT_LAMBDA
#define RT_LAMBDA

#include "Runtime.h"

RTValue *RTLambdaValueBridge(RTLambda *lambda);

RTLambda *RTLambdaDecode(RTByte **code);

void RTLambdaDealloc(RTLambda *lambda);

void RTLambdaSetContextValueAtIndex(RTLambda *lambda, RTValue *value, RTInteger32Bit index);

RTInteger64Bit RTLambdaHash(RTLambda *lambda);

bool RTLambdaEqual(RTLambda *lambda, RTLambda *other);

RTInteger32Bit RTLambdaRegisterCount(RTLambda *lambda);

RTError RTLambdaExecute(RTLambda *lambda, RTValue **reg, RTInteger8Bit arity, RTPool *pool);

void RTLambdaEnumerateContext(RTLambda *lambda, RTBlock *block);

#endif
