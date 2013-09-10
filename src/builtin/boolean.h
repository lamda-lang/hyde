#ifndef BUILTIN_BOOLEAN_H
#define BUILTIN_BOOLEAN_H

#include <runtime.h>

Value *BooleanDecodeTrue(Byte **bytes);
Value *BooleanDecodeFalse(Byte **bytes);
void BooleanRelease(void *booleanData);
Bool BooleanEqual(void *booleanData, void *otherData);

#endif
