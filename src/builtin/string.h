#ifndef BUILTIN_STRING_H
#define BUILTIN_STRING_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *StringDecode(Byte **bytes, Error *error);
void StringDealloc(VALUE *stringValue);

#endif
