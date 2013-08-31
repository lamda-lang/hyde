#ifndef RANGE_H
#define RANGE_H

#include "api.h"

VALUE *RangeDecode(Byte **bytes, Error *error);
void RangeDealloc(VALUE *rangeValue);

#endif
