#ifndef BUILTIN_SET_H
#define BUILTIN_SET_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *SetDecode(Byte **bytes, Error *error);
void SetDealloc(VALUE *setValue);

#endif
