#ifndef RANGE_H
#define RANGE_H

#include "runtime.h"

VALUE *RangeDecode(Byte **bytes, VALUE **error);
void RangeDealloc(VALUE *rangeValue);
Integer64 RangeHash(VALUE *rangeValue);

#endif
