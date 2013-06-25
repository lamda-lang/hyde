#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "api.h"

Value *BooleanTrueSingleton(void);
Value *BooleanFalseSingleton(void);
void *BooleanDecodeTrue(Byte **bytes, Error *error);
void *BooleanDecodeFalse(Byte **bytes, Error *error);
Value *BooleanEval(void *data, Code *code, Value **context, bool pure, Error *error);
void BooleanDealloc(Value *booleanValue);
Integer64 BooleanHash(Value *booleanValue);
bool BooleanEqual(Value *booleanValue, Value *otherValue);

#endif
