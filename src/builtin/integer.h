#ifndef BUILTIN_INTEGER_H
#define BUILTIN_INTEGER_H

#include <runtime.h>

typedef struct Integer Integer;

Integer *IntegerDecode(Byte **bytes);
Value *IntegerEqual(Integer *integer, Integer *other);
Size IntegerRelease(Integer *integer);

#endif
