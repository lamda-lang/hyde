#ifndef RESULT_H
#define RESULT_H

#include "api.h"

Value *ResultValueBridge(Result *result);

Result *ResultDecode(Byte **bytes, Error *error);

void ResultDealloc(Result *result);

Integer8 ResultArity(Result *result);

void ResultSetLambda(Result *result, Lambda *lambda);

void ResultSetArgAtIndex(Result *result, Value *arg, Integer8 index);

#endif
