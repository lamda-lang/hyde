#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "runtime.h"

Size BooleanSize(Boolean *boolean);
Size BooleanEncode(Boolean *boolean, Byte **bytes);
Boolean *BooleanDecode(Byte **bytes, Error *error);
Bool BooleanEqual(Boolean *boolean, Boolean *other);
Size BooleanRelease(Boolean *boolean);

#endif
