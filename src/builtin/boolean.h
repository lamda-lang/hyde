#ifndef BUILTIN_BOOLEAN_H
#define BUILTIN_BOOLEAN_H

#include <runtime.h>

Value *BooleanDecodeTrue(Byte **bytes, Error *error);
Value *BooleanDecodeFalse(Byte **bytes, Error *error);
void BooleanRelease(void *booleanModel);
Bool BooleanEqual(void *booleanModel, void *otherModel);

#endif
