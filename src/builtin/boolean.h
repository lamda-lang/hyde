#ifndef BUILTIN_BOOLEAN_H
#define BUILTIN_BOOLEAN_H

#include <runtime.h>

typedef struct Boolean Boolean;

Value *BooleanCreate(Bool truth);
Size BooleanRelease(Boolean *boolean);
Bool BooleanEqual(Boolean *boolean, Boolean *other);

#endif
