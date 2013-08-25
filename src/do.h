#ifndef DO_H
#define DO_H

#include "runtime.h"

VALUE *DoDecode(Byte **bytes, VALUE **error);
void DoDealloc(VALUE *doVALUE);
Integer64 DoHash(VALUE *doVALUE);
void DoEnumerate(VALUE *doVALUE, void (*callback)(VALUE *value));

#endif
