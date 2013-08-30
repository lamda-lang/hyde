#ifndef NIL_H
#define NIL_H

#include "runtime.h"

VALUE *NilDecode(Byte **bytes, Error *error);
void NilDealloc(VALUE *nilValue);

#endif
