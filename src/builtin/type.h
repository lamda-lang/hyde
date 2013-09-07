#ifndef BUILTIN_TYPE_H
#define BUILTIN_TYPE_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *TypeCreate(Integer32 count, Error *error);
VALUE *TypeBootstrap(Error *error);
VALUE *TypeDecode(Byte **bytes, Error *error);
void TypeDealloc(VALUE *typeValue);

#endif
