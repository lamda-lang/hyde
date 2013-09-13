#ifndef BUILTIN_BOOLEAN_H
#define BUILTIN_BOOLEAN_H

#include <runtime.h>

typedef struct Boolean Boolean;

Value *BooleanDecodeTrue(Byte **bytes);
Value *BooleanDecodeFalse(Byte **bytes);
Size BooleanRelease(Boolean *boolean);
Bool BooleanEqual(Boolean *boolean, Boolean *other);

#endif
