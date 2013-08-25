#ifndef SET_H
#define SET_H

#include "runtime.h"

VALUE *SetDecode(Byte **bytes, VALUE **error);
void SetDealloc(VALUE *setValue);
Integer64 SetHash(VALUE *setValue);

#endif
