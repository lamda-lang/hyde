#ifndef BUILTIN_FLOAT_H
#define BUILTIN_FLOAT_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *FloatDecode(Byte **bytes, Error *error);
void FloatDealloc(VALUE *floatValue);

#endif
