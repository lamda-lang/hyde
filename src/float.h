#ifndef FLOAT_H
#define FLOAT_H

#include "runtime.h"

VALUE *FloatDecode(Byte **bytes, VALUE **error);
void FloatDealloc(VALUE *floatValue);
Integer64 FloatHash(VALUE *floatValue);
Bool FloatEqual(VALUE *floatValue, VALUE *otherValue);

#endif
