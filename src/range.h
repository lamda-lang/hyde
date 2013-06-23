#ifndef RANGE_H
#define RANGE_H

#include "api.h"

void *RangeDecode(Byte **bytes, Error *error);
Value *RangeEval(void *data, Code *code, bool pure, Error *error);
void RangeDealloc(Value *rangeValue);
Integer64 RangeHash(Value *rangeValue);
void RangeEnumerate(Value *rangeValue, void (*callback)(Value *value));

#endif
