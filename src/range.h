#ifndef RANGE_H
#define RANGE_H

#include "runtime.h"

VALUE *RangeDecode(Byte **bytes, VALUE **error);
void RangeDealloc(VALUE *rangeVALUE);
Integer64 RangeHash(VALUE *rangeVALUE);
void RangeEnumerate(VALUE *rangeVALUE, void (*callback)(VALUE *value));

#endif
