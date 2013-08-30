#ifndef SET_H
#define SET_H

#include "runtime.h"

VALUE *SetDecode(Byte **bytes, Error *error);
void SetDealloc(VALUE *setValue);

#endif
