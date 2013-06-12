#ifndef RANGE_H
#define RANGE_H

#include "api.h"

Value *RangeValueBridge(Range *range);

void RangeDealloc(Value *rangeValue);

void RangeFetch(Value *rangeValue, Value **values);

Integer64 RangeHash(Value *rangeValue);

void RangeEnumerate(Value *rangeValue, void (*callback)(Value *value));

Value *RangeDecode(Byte **bytes, Error *error);

Value *RangeDecodeLower(Byte **bytes, Error *error);

Value *RangeDecodeUpper(Byte **bytes, Error *error);

Value *RangeEval(Value *rangeValue, bool pure, Error *error);

#endif
