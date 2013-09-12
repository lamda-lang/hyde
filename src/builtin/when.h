#ifndef BUILTIN_WHEN_H
#define BUILTIN_WHEN_H

#include <runtime.h>

Value *WhenDecode(Byte **bytes);
void WhenRelease(When *block);
Bool WhenEqual(When *block, When *other);

#endif
