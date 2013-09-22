#ifndef RANGE_H
#define RANGE_H

#include "runtime.h"

Range *RangeDecode(Byte **bytes, Error *error);
Range *RangeEval(Range *range, Value *context, Error *error);
Bool RangeEqual(Range *range, Range *other);
Size RangeRelease(Range *range);

#endif
