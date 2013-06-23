#ifndef SET_H
#define SET_H

#include "api.h"

void *SetDecode(Byte **bytes, Error *error);
Value *SetEval(void *data, Code *code, bool pure, Error *error);
void SetDealloc(Value *setValue);
Integer64 SetHash(Value *setValue);
void SetEnumerate(Value *setValue, void (*callback)(Value *value));

#endif
