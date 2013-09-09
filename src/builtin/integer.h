#ifndef INTEGER_H
#define INTEGER_H

#include <runtime.h>

Value *IntegerDecode(Byte **bytes, Error *error);
Bool IntegerEqual(Value *integerValue, Value *otherValue);
void IntegerRelease(Value *integerValue);

#endif
