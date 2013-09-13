#ifndef BUILTIN_RANGE_H
#define BUILTIN_RANGE_H

#include <runtime.h>

typedef struct Range Range;

Value *RangeDecode(Byte **bytes);
Size RangeRelease(Range *range);
Bool RangeEqual(Range *range, Range *other);

#endif
