#ifndef RANGE_H
#define RANGE_H

#include "api.h"

void *RangeDecode(Byte **bytes, Value **error);
void RangeDealloc(Value *rangeValue);
Integer64 RangeHash(Value *rangeValue);
void RangeEnumerate(Value *rangeValue, void (*callback)(Value *value));

#endif
