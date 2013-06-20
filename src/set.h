#ifndef SET_H
#define SET_H

#include "api.h"

Value *SetDecode(Byte **bytes, Error *error);
void SetFetch(Value *setValue, Byte **values);
void SetDealloc(Value *setValue);
Integer64 SetHash(Value *setValue);
void SetEnumerate(Value *setValue, void (*callback)(Value *value));
Value *SetEval(Value *setValue, bool pure, Error *error);

#endif
