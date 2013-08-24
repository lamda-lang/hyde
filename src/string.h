#ifndef STRING_H
#define STRING_H

#include "runtime.h"

VALUE *StringDecode(Byte **bytes, VALUE **error);
void StringDealloc(VALUE *stringValue);
Integer64 StringHash(VALUE *stringValue);
Bool StringEqual(VALUE *stringValue, VALUE *otherValue);

/* kernels */
VALUE *StringConcatenate(VALUE **args, Integer8 count, VALUE **error);

#endif
