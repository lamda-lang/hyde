#ifndef BUILTIN_INTEGER_H
#define BUILTIN_INTEGER_H

#include <runtime.h>

Value *IntegerDecode(Byte **bytes);
Bool IntegerEqual(Integer *integer, Integer *other);
void IntegerRelease(Integer *integer);

#endif
