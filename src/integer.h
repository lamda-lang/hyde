#ifndef INTEGER_H
#define INTEGER_H

#include "runtime.h"

Size IntegerSize(Integer *integer);
Integer *IntegerDecode(Byte **bytes, Error *error);
Bool IntegerEqual(Integer *integer, Integer *other);
Size IntegerRelease(Integer *integer);

#endif
