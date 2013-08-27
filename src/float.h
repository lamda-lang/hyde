#ifndef FLOAT_H
#define FLOAT_H

#include "runtime.h"

VALUE *FloatDecode(Byte **bytes, VALUE **error);
void FloatDealloc(VALUE *floatValue);

#endif
