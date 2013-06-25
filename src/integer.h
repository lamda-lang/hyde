#ifndef INTEGER_H
#define INTEGER_H

#include "api.h"

void *IntegerDecode(Byte **bytes, Error *error);
Value *IntegerEval(void *data, Code *code, bool pure, Error *error);
void IntegerDealloc(Value *integerValue);
Integer64 IntegerHash(Value *integerValue);
bool IntegerEqual(Value *integerValue, Value *otherValue);

/* kernels */
Value *IntegerSum(Value **args, Integer8 count, Error *error);

#endif
