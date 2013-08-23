#ifndef INTEGER_H
#define INTEGER_H

#include "api.h"

void *IntegerDecode(Byte **bytes, Value **error);
void IntegerDealloc(Value *integerValue);
Integer64 IntegerHash(Value *integerValue);
Bool IntegerEqual(Value *integerValue, Value *otherValue);

/* kernels */
Value *IntegerSum(Value **args, Integer8 count, Value **error);

#endif
