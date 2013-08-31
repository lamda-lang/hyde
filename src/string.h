#ifndef STRING_H
#define STRING_H

#include "api.h"

VALUE *StringDecode(Byte **bytes, Error *error);
void StringDealloc(VALUE *stringValue);

#endif
