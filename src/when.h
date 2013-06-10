#ifndef WHEN_H
#define WHEN_H

#include "api.h"

Value *WhenValueBridge(When *block);

Value *WhenDecode(Byte **bytes, Error *error);

void WhenFetch(Value *whenValue, Value **values);

Value *WhenEval(Value *whenValue, Error *error);

void WhenDealloc(Value *whenValue);

#endif