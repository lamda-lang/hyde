#ifndef BUILTIN_WHEN_H
#define BUILTIN_WHEN_H

#include <runtime.h>

typedef struct When When;

Value *WhenDecode(Byte **bytes);
Size WhenRelease(When *block);
Bool WhenEqual(When *block, When *other);

#endif
