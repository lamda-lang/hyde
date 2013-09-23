#ifndef WHEN_H
#define WHEN_H

#include "runtime.h"

Size WhenSize(When *block);
void WhenEncode(When *block, Byte **bytes);
When *WhenDecode(Byte **bytes, Error *error);
Value *WhenEval(When *block, Value *context, Error *error);
Bool WhenEqual(When *block, When *other);
Size WhenRelease(When *block);

#endif
