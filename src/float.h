#ifndef FLOAT_H
#define FLOAT_H

#include "api.h"

Value *FloatDecode(Byte **bytes, Error *error);

Value *FloatValueBridge(Float *fpv);

void FloatDealloc(Value *floatValue);

Integer64 FloatHash(Value *floatValue);

Float *FloatSum(Float *fpv, Float *other, Error *error);

Value *FloatEval(Value *floatValue, bool pure, Error *error);

#endif
