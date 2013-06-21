#ifndef NIL_H
#define NIL_H

#include "api.h"

Value *NilCreate(Error *error);
void NilDealloc(Value *nilValue);
Integer64 NilHash(Value *nilValue);
bool NilEqual(Value *nilValue, Value *otherValue);
Value *NilDecode(Byte **bytes, Error *error);
Value *NilEval(Value *nilValue, bool pure, Error *error);

#endif
