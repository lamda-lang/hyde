#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "api.h"

Value *BooleanTrueSingleton(void);
Value *BooleanFalseSingleton(void);
void *BooleanDecodeTrue(Byte **bytes, Value **error);
void *BooleanDecodeFalse(Byte **bytes, Value **error);
void BooleanDealloc(Value *booleanValue);
Integer64 BooleanHash(Value *booleanValue);
Bool BooleanEqual(Value *booleanValue, Value *otherValue);

#endif
