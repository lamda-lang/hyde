#ifndef INTEGER_H
#define INTEGER_H

#include "api.h"

Value *IntegerDecode(Byte **bytes, Error *error);

Value *IntegerValueBridge(Integer *integer);

void IntegerDealloc(Value *integerValue);

Integer64 IntegerHash(Value *integerValue);

Integer *IntegerSum(Integer *integer, Integer *other, Error *error);

#endif
