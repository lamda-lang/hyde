#ifndef INTEGER_H
#define INTEGER_H

#include "runtime.h"

Value *IntegerValueBridge(Integer *integer);

void IntegerDealloc(Value *integer_Integer);

Integer *IntegerDecode(Byte **data);

Integer64Bit IntegerHash(Value *integer_Integer);

Integer *IntegerSum(Integer *integer, Integer *other);

#endif
