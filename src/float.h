#ifndef FLOAT_H
#define FLOAT_H

#include "api.h"

void *FloatDecode(Byte **bytes, Value **error);
void FloatDealloc(Value *floatValue);
Integer64 FloatHash(Value *floatValue);
Bool FloatEqual(Value *floatValue, Value *otherValue);
Value *FloatSum(Value *floatValue, Value *otherValue, Value **error);

#endif
