#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "api.h"

VALUE *BooleanCreate(Bool truth, Error *error);
VALUE *BooleanDecodeTrue(Byte **bytes, Error *error);
VALUE *BooleanDecodeFalse(Byte **bytes, Error *error);
void BooleanDealloc(VALUE *booleanValue);

#endif
