#ifndef SET_H
#define SET_H

#include "api.h"

Set *SetDecode(Byte **bytes, Error *error);

void SetFetch(Set *set, Value **values, Byte **bytes);

Value *SetValueBridge(Set *set);

void SetDealloc(Value *setValue);

Integer64 SetHash(Value *setValue);

void SetEnumerate(Value *setValue, void (*block)(Value *value));

#endif
