#ifndef LAMBDA_H
#define LAMBDA_H

#include "api.h"

Value *LambdaValueBridge(Lambda *lambda);

Value *LambdaDecode(Byte **bytes, Error *error);

void LambdaFetch(Value *lambdaValue, Value **values);

void LambdaDealloc(Value *lambdaValue);

Integer64 LambdaHash(Value *lambdaValue);

void LambdaEnumerate(Value *lambdaValue, void (*callback)(Value *value));

#endif
