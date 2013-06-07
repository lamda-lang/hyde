#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "api.h"

Value *BooleanTrueSingleton(void);

Value *BooleanFalseSingleton(void);

Integer64 BooleanHash(Value *booleanValue);

Value *BooleanDecodeTrue(Byte **bytes, Error *error);

Value *BooleanDecodeFalse(Byte **bytes, Error *error);

#endif
