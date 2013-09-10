#ifndef BUILTIN_RANGE_H
#define BUILTIN_RANGE_H

#include <runtime.h>

Value *RangeDecode(Byte **bytes);
void RangeRelease(void *rangeData);
Bool RangeEqual(void *rangeData, void *otherData);

#endif
