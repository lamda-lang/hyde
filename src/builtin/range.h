#ifndef BUILTIN_RANGE_H
#define BUILTIN_RANGE_H

#include <runtime.h>

Value *RangeDecode(Byte **bytes);
void RangeRelease(Range *range);
Bool RangeEqual(Range *range, Range *other);

#endif
