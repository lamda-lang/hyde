#ifndef FLOAT_H
#define FLOAT_H

#include <runtime.h>

VALUE *FloatDecode(Byte **bytes, Error *error);
void FloatDealloc(VALUE *floatValue);

#endif
