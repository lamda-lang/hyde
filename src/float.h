#ifndef FLOAT_H
#define FLOAT_H

#include "api.h"

Float *FloatDecode(Byte **bytes, Error *error);

Value *FloatValueBridge(Float *fpv);

void FloatDealloc(Value *floatValue);

Integer64 FloatHash(Value *floatValue);

Float *FloatSum(Float *fpv, Float *other, Error *error);

#endif