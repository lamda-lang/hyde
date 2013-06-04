#ifndef LAMBDA_H
#define LAMBDA_H

#include "api.h"

Value *LambdaValueBridge(Lambda *lambda);

Lambda *LambdaDecode(Byte **bytes, Error *error);

void LambdaDealloc(Value *lambdaValue);

void LambdaSetContextValueAtIndex(Lambda *lambda, Value *value, Integer8 index);

Integer8 LambdaContextLength(Lambda *lambda);

Integer8 LambdaArity(Lambda *lambda);

Integer64 LambdaHash(Value *lambdaValue);

Integer32 LambdaRegisterCount(Lambda *lambda);

Status LambdaExecute(Lambda *lambda, Byte **bytes, Stack *stack, Error *error);

void LambdaEnumerate(Value *lambdaValue, void (*block)(Value *value));

#endif
