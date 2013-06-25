#ifndef NIL_H
#define NIL_H

#include "api.h"

Value *NilSingleton(void);
void *NilDecode(Byte **bytes, Error *error);
Value *NilEval(void *data, Code *code, Value **context, bool pure, Error *error);
void NilDealloc(Value *nilValue);
Integer64 NilHash(Value *nilValue);
bool NilEqual(Value *nilValue, Value *otherValue);

#endif
