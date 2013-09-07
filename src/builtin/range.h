#ifndef RANGE_H
#define RANGE_H

#include <runtime.h>

VALUE *RangeDecode(Byte **bytes, Error *error);
void RangeDealloc(VALUE *rangeValue);

#endif
