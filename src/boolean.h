#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "runtime.h"

VALUE *BooleanDecodeTrue(Byte **bytes, VALUE **error);
VALUE *BooleanDecodeFalse(Byte **bytes, VALUE **error);
void BooleanDealloc(VALUE *booleanValue);
Integer64 BooleanHash(VALUE *booleanValue);
Bool BooleanEqual(VALUE *booleanValue, VALUE *otherValue);

#endif
