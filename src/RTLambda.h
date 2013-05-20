#ifndef RT_LAMBDA
#define RT_LAMBDA

#include "runtime.h"

RTValue *RTLambdaValueBridge(RTLambda *lambda);

RTLambda *RTLambdaDecode(RTByte **code);

void RTLambdaDealloc(RTValue *lambda_RTLambda);

void RTLambdaSetContextValueAtIndex(RTLambda *lambda, RTValue *value, RTInteger32Bit index);

RTInteger64Bit RTLambdaHash(RTValue *lambda_RTLambda);

RTInteger32Bit RTLambdaRegisterCount(RTLambda *lambda);

RTStatus RTLambdaExecute(RTLambda *lambda, RTStack *stack, RTInteger8Bit arity);

void RTLambdaEnumerate(RTValue *lambda_RTLambda, RTBlock *block);

#endif
