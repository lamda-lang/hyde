#ifndef INTEGER_H
#define INTEGER_H

#include "runtime.h"

VALUE *IntegerDecode(Byte **bytes, Error *error);
void IntegerDealloc(VALUE *integerValue);

#endif
