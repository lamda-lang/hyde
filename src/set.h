#ifndef SET_H
#define SET_H

#include "api.h"

Value *SetDecode(Byte **bytes, Error *error);

void SetFetch(Value *setValue, Byte **values);

Value *SetValueBridge(Set *set);

void SetDealloc(Value *setValue);

Integer64 SetHash(Value *setValue);

void SetEnumerate(Value *setValue, void (*callback)(Value *value));

Value *SetEval(Value *setValue, Error *error);

#endif
