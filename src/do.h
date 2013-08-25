#ifndef DO_H
#define DO_H

#include "runtime.h"

VALUE *DoDecode(Byte **bytes, VALUE **error);
void DoDealloc(VALUE *doValue);
Integer64 DoHash(VALUE *doValue);

#endif
