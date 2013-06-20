#ifndef WHEN_H
#define WHEN_H

#include "api.h"

Value *WhenDecode(Byte **bytes, Error *error);
void WhenFetch(Value *whenValue, Value **values);
Value *WhenEval(Value *whenValue, bool pure, Error *error);
void WhenDealloc(Value *whenValue);

#endif
