#ifndef BUILTIN_BOOLEAN_H
#define BUILTIN_BOOLEAN_H

#include <runtime.h>

Value *BooleanDecodeTrue(Byte **bytes);
Value *BooleanDecodeFalse(Byte **bytes);
void BooleanRelease(Boolean *boolean);
Bool BooleanEqual(Boolean *boolean, Boolean *other);

#endif
