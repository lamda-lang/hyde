#ifndef RANGE_H
#define RANGE_H

#include "api.h"

Range *RangeCreate(Error *error);

Value *RangeValueBridge(Range *range);

void RangeDealloc(Value *rangeValue);

void RangeSetBounds(Range *range, Value *lower, Value *upper);

Integer64 RangeHash(Value *rangeValue);

void RangeEnumerate(Value *rangeValue, void (*block)(Value *value));

#endif
