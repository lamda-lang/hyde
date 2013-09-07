#ifndef BUILTIN_RANGE_H
#define BUILTIN_RANGE_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *RangeDecode(Byte **bytes, Error *error);
void RangeDealloc(VALUE *rangeValue);

#endif
