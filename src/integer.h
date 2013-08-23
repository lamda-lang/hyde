#ifndef INTEGER_H
#define INTEGER_H

#include "api.h"

void *IntegerDecode(Byte **bytes, VALUE **error);
void IntegerDealloc(VALUE *integerVALUE);
Integer64 IntegerHash(VALUE *integerVALUE);
Bool IntegerEqual(VALUE *integerVALUE, VALUE *otherVALUE);

/* kernels */
VALUE *IntegerSum(VALUE **args, Integer8 count, VALUE **error);

#endif
