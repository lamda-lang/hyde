#ifndef BUILTIN_BOOLEAN_H
#define BUILTIN_BOOLEAN_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *BooleanCreate(Bool truth, Error *error);
VALUE *BooleanDecodeTrue(Byte **bytes, Error *error);
VALUE *BooleanDecodeFalse(Byte **bytes, Error *error);
void BooleanDealloc(VALUE *booleanValue);

#endif
