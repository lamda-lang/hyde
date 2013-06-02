#ifndef SET_H
#define SET_H

#include "api.h"

Set *SetDecode(Byte **bytes, Error *error);

Integer32 SetCount(Set *set);

void SetAddValue(Set *set, Value *value);

Value *SetValueBridge(Set *set);

void SetDealloc(Value *setValue);

Integer64 SetHash(Value *setValue);

void SetEnumerate(Value *setValue, void (*block)(Value *value));

#endif
