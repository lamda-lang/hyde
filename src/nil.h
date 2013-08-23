#ifndef NIL_H
#define NIL_H

#include "api.h"

Value *NilSingleton(void);
void *NilDecode(Byte **bytes, Value **error);
void NilDealloc(Value *nilValue);
Integer64 NilHash(Value *nilValue);
Bool NilEqual(Value *nilValue, Value *otherValue);

#endif
