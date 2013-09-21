#ifndef INTEGER_H
#define INTEGER_H

#include "runtime.h"

Integer *IntegerDecode(Byte **bytes);
Bool IntegerEqual(Integer *integer, Integer *other);
Size IntegerRelease(Integer *integer);

#endif
