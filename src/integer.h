#ifndef INTEGER_H
#define INTEGER_H

#include "api.h"

Integer *IntegerCreate(Integer64 value, Exception *exception);

Value *IntegerValueBridge(Integer *integer);

void IntegerDealloc(Value *integerValue);

Integer64 IntegerHash(Value *integerValue);

Integer *IntegerSum(Integer *integer, Integer *other, Exception *exception);

#endif
