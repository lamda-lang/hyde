#ifndef BUILTIN_RANGE_H
#define BUILTIN_RANGE_H

#include <runtime.h>

typedef struct Range Range;

Range *RangeDecode(Byte **bytes);
Range *RangeEval(Range *range, Value *context);
Bool RangeEqual(Range *range, Range *other);
Size RangeRelease(Range *range);

#endif
