#ifndef INTEGER_H
#define INTEGER_H

#include "api.h"

VALUE *IntegerDecode(Byte **bytes, Error *error);
void IntegerDealloc(VALUE *integerValue);

#endif
