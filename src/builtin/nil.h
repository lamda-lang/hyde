#ifndef BUILTIN_NIL_H
#define BUILTIN_NIL_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *NilCreate(Error *error);
VALUE *NilDecode(Byte **bytes, Error *error);
void NilDealloc(VALUE *nilValue);

#endif
