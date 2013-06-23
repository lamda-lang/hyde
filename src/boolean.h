#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "api.h"

void *BooleanDecodeTrue(Byte **bytes, Error *error);
void *BooleanDecodeFalse(Byte **bytes, Error *error);
Value *BooleanEval(void *data, Code *code, bool pure, Error *error);
Value *BooleanCreate(bool truth, Error *error);
void BooleanDealloc(Value *booleanValue);
Integer64 BooleanHash(Value *booleanValue);
bool BooleanEqual(Value *booleanValue, Value *otherValue);

#endif
