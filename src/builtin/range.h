#ifndef RANGE_H
#define RANGE_H

#include <runtime.h>

Value *RangeDecode(Byte **bytes, Error *error);
void RangeDealloc(Value *rangeValue);

#endif
