#ifndef RANGE_H
#define RANGE_H

#include "runtime.h"

Range *RangeDecode(Byte **bytes);
Range *RangeEval(Range *range, Value *context);
Bool RangeEqual(Range *range, Range *other);
Size RangeRelease(Range *range);

#endif
