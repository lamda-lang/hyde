#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "api.h"

Value *BooleanCreate(bool truth, Error *error);
Integer64 BooleanHash(Value *booleanValue);
Value *BooleanDecodeTrue(Byte **bytes, Error *error);
Value *BooleanDecodeFalse(Byte **bytes, Error *error);
Value *BooleanEval(Value *booleanValue, bool pure, Error *error);

#endif
