#ifndef LAMBDA_H
#define LAMBDA_H

#include "runtime.h"

Value *LambdaValueBridge(Lambda *lambda);

Lambda *LambdaDecode(Byte **code);

void LambdaDealloc(Value *lambda_Lambda);

void LambdaSetContextValueAtIndex(Lambda *lambda, Value *value, Integer32Bit index);

Integer64Bit LambdaHash(Value *lambda_Lambda);

Integer32Bit LambdaRegisterCount(Lambda *lambda);

Status LambdaExecute(Lambda *lambda, Stack *stack, Integer8Bit arity);

void LambdaEnumerate(Value *lambda_Lambda, void (*block)(Value *value));

#endif
