#ifndef SET_H
#define SET_H

#include "runtime.h"

void *SetDecode(Byte **bytes, VALUE **error);
void SetDealloc(VALUE *setVALUE);
Integer64 SetHash(VALUE *setVALUE);
void SetEnumerate(VALUE *setVALUE, void (*callback)(VALUE *value));

#endif
