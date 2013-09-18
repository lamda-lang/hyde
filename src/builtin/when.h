#ifndef BUILTIN_WHEN_H
#define BUILTIN_WHEN_H

#include <runtime.h>

typedef struct When When;

When *WhenDecode(Byte **bytes);
Value *WhenEval(When *block, Value *context);
Bool WhenEqual(When *block, When *other);
Size WhenRelease(When *block);

#endif
