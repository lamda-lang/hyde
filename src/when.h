#ifndef WHEN_H
#define WHEN_H

#include "runtime.h"

When *WhenDecode(Byte **bytes);
Value *WhenEval(When *block, Value *context);
Bool WhenEqual(When *block, When *other);
Size WhenRelease(When *block);

#endif
