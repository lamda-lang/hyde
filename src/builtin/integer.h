#ifndef BUILTIN_INTEGER_H
#define BUILTIN_INTEGER_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *IntegerDecode(Byte **bytes, Error *error);
void IntegerDealloc(VALUE *integerValue);

#endif
