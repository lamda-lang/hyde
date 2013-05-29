#ifndef LAMBDA_H
#define LAMBDA_H

#include "api.h"

Value *LambdaValueBridge(Lambda *lambda);

Lambda *LambdaDecode(Byte **bytes, Exception *exception);

void LambdaDealloc(Value *lambdaValue);

void LambdaSetContextValueAtIndex(Lambda *lambda, Value *value, Integer32 index);

Integer64 LambdaHash(Value *lambdaValue);

Integer32 LambdaRegisterCount(Lambda *lambda);

Status LambdaExecute(Lambda *lambda, Stack *stack, Integer8 arity, Exception *exception);

void LambdaEnumerate(Value *lambdaValue, void (*block)(Value *value));

#endif
