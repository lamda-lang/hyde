#ifndef NIL_H
#define NIL_H

#include "runtime.h"

VALUE *NilSingleton(void);
void *NilDecode(Byte **bytes, VALUE **error);
void NilDealloc(VALUE *nilVALUE);
Integer64 NilHash(VALUE *nilVALUE);
Bool NilEqual(VALUE *nilVALUE, VALUE *otherVALUE);

#endif
