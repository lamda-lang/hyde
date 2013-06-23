#ifndef NIL_H
#define NIL_H

#include "api.h"

void *NilDecode(Byte **bytes, Error *error);
Value *NilEval(void *data, Code *code, bool pure, Error *error);
Value *NilCreate(Error *error);
void NilDealloc(Value *nilValue);
Integer64 NilHash(Value *nilValue);
bool NilEqual(Value *nilValue, Value *otherValue);

#endif
