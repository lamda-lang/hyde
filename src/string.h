#ifndef STRING_H
#define STRING_H

#include "runtime.h"

VALUE *StringDecode(Byte **bytes, VALUE **error);
void StringDealloc(VALUE *stringValue);

#endif
