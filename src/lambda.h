#ifndef LAMBDA_H
#define LAMBDA_H

#include "api.h"

Value *LambdaValueBridge(Lambda *lambda);

Lambda *LambdaDecode(Byte **bytes, Error *error);

void LambdaDealloc(Value *lambdaValue);

void LambdaFetch(Lambda *lambda, Value **values, Byte **bytes);

Integer64 LambdaHash(Value *lambdaValue);

Integer32 LambdaRegisterCount(Lambda *lambda);

Status LambdaExecute(Lambda *lambda, Stack *stack, Integer8 arity, Error *error);

void LambdaEnumerate(Value *lambdaValue, void (*block)(Value *value));

#endif
