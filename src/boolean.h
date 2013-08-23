#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "api.h"

void BooleanDealloc(VALUE *booleanVALUE);
Integer64 BooleanHash(VALUE *booleanVALUE);
Bool BooleanEqual(VALUE *booleanVALUE, VALUE *otherVALUE);

#endif
