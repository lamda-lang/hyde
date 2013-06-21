#ifndef INTEGER_H
#define INTEGER_H

#include "api.h"

Value *IntegerDecode(Byte **bytes, Error *error);
void IntegerDealloc(Value *integerValue);
Integer64 IntegerHash(Value *integerValue);
bool IntegerEqual(Value *integerValue, Value *otherValue);
Value *IntegerSum(Value *integerValue, Value *otherValue, Error *error);
Value *IntegerEval(Value *integerValue, bool pure, Error *error);

#endif
