#ifndef INTEGER_H
#define INTEGER_H

#include "runtime.h"

VALUE *IntegerDecode(Byte **bytes, VALUE **error);
void IntegerDealloc(VALUE *integerValue);
Integer64 IntegerHash(VALUE *integerValue);
Bool IntegerEqual(VALUE *integerValue, VALUE *otherValue);

/* kernels */
VALUE *IntegerSum(VALUE **args, Integer8 count, VALUE **error);

#endif
