#ifndef NIL_H
#define NIL_H

#include "api.h"

VALUE *NilCreate(Error *error);
VALUE *NilDecode(Byte **bytes, Error *error);
void NilDealloc(VALUE *nilValue);

#endif
