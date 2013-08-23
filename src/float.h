#ifndef FLOAT_H
#define FLOAT_H

#include "api.h"

void *FloatDecode(Byte **bytes, VALUE **error);
void FloatDealloc(VALUE *floatVALUE);
Integer64 FloatHash(VALUE *floatVALUE);
Bool FloatEqual(VALUE *floatVALUE, VALUE *otherVALUE);
VALUE *FloatSum(VALUE *floatVALUE, VALUE *otherVALUE, VALUE **error);

#endif
