#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "runtime.h"

void BooleanDealloc(VALUE *booleanVALUE);
Integer64 BooleanHash(VALUE *booleanVALUE);
Bool BooleanEqual(VALUE *booleanVALUE, VALUE *otherVALUE);

#endif
