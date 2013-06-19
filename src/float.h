#ifndef FLOAT_H
#define FLOAT_H

#include "api.h"

Value *FloatDecode(Byte **bytes, Error *error);

void FloatDealloc(Value *floatValue);

Integer64 FloatHash(Value *floatValue);

Value *FloatSum(Value *floatValue, Value *otherValue, Error *error);

Value *FloatEval(Value *floatValue, bool pure, Error *error);

#endif
