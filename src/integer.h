#ifndef INTEGER_H
#define INTEGER_H

#include "runtime.h"

Integer *IntegerDecode(Byte **bytes, Error *error);
Bool IntegerEqual(Integer *integer, Integer *other);
Size IntegerRelease(Integer *integer);

#endif
