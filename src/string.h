#ifndef STRING_H
#define STRING_H

#include "runtime.h"

VALUE *StringDecode(Byte **bytes, VALUE **error);
VALUE *StringCreateWithCharacters(Char *chars, VALUE **error);
void StringDealloc(VALUE *stringVALUE);
Integer64 StringHash(VALUE *stringVALUE);
Bool StringEqual(VALUE *stringVALUE, VALUE *otherVALUE);

/* kernels */
VALUE *StringConcatenate(VALUE **args, Integer8 count, VALUE **error);
VALUE *StringPrint(VALUE **args, Integer8 count, VALUE **error);

#endif
