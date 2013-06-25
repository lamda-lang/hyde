#ifndef FLOAT_H
#define FLOAT_H

#include "api.h"

void *FloatDecode(Byte **bytes, Error *error);
Value *FloatEval(void *data, Code *code, Value **context, bool pure, Error *error);
void FloatDealloc(Value *floatValue);
Integer64 FloatHash(Value *floatValue);
bool FloatEqual(Value *floatValue, Value *otherValue);
Value *FloatSum(Value *floatValue, Value *otherValue, Error *error);

#endif
