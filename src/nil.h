#ifndef NIL_H
#define NIL_H

#include "runtime.h"

VALUE *NilDecode(Byte **bytes, VALUE **error);
void NilDealloc(VALUE *nilValue);

#endif
