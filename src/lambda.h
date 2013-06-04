#ifndef LAMBDA_H
#define LAMBDA_H

#include "api.h"

Value *LambdaValueBridge(Lambda *lambda);

Lambda *LambdaDecode(Byte **bytes, Error *error);

void LambdaDealloc(Value *lambdaValue);

void LambdaSetContextValueAtIndex(Lambda *lambda, Value *value, Integer8 index);

Integer8 LambdaContextLength(Lambda *lambda);

Integer64 LambdaHash(Value *lambdaValue);

Value *LambdaExecute(Lambda *lambda, Args *args, Stack *stack, Error *error);

void LambdaEnumerate(Value *lambdaValue, void (*block)(Value *value));

Args *ArgsDecode(Byte **bytes, Error *error);

Integer8 ArgsCount(Args *args);

Value **ArgsValues(Args *args);

#endif
