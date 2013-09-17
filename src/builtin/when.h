#ifndef BUILTIN_WHEN_H
#define BUILTIN_WHEN_H

#include <runtime.h>

typedef struct When When;

Value *WhenDecode(Byte **bytes);
Value *WhenEval(When *block, Value *context);
Value *WhenEqual(When *block, When *other);
Size WhenRelease(When *block);

#endif
