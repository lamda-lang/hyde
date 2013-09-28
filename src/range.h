#ifndef RANGE_H
#define RANGE_H

#include "runtime.h"

Size RangeSize(Range *range);
Size RangeEncode(Range *range, Byte **bytes);
Range *RangeDecode(Byte **bytes, Error *error);
Value *RangeEval(Value *value, Range *range, Value *context, Error *error);
Bool RangeEqual(Range *range, Range *other);
Size RangeRelease(Range *range);

#endif
