#ifndef INTEGER_H
#define INTEGER_H

#include "api.h"

Integer *IntegerCreate(Integer64 value, Exception *exception);

Value *IntegerValueBridge(Integer *integer);

void IntegerDealloc(Value *integer);

Integer64 IntegerHash(Value *integer);

Integer *IntegerSum(Integer *integer, Integer *other, Exception *exception);

#endif
