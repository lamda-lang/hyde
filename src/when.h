#ifndef WHEN_H
#define WHEN_H

#include "api.h"

Value *WhenValueBridge(When *block);

Value *WhenDecode(Byte **bytes, Error *error);

void WhenFetch(Value *whenValue, Value **values);

Value *WhenValue(When *block);

void WhenDealloc(Value *whenValue);

void WhenEnumerate(Value *whenValue, void (*callback)(Value *value));

#endif
