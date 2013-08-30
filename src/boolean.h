#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "runtime.h"

VALUE *BooleanDecodeTrue(Byte **bytes, Error *error);
VALUE *BooleanDecodeFalse(Byte **bytes, Error *error);
void BooleanDealloc(VALUE *booleanValue);

#endif
