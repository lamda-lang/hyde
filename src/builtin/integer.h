#ifndef BUILTIN_INTEGER_H
#define BUILTIN_INTEGER_H

#include <runtime.h>

Value *IntegerDecode(Byte **bytes);
Bool IntegerEqual(void *integerData, void *otherData);
void IntegerRelease(void *integerData);

#endif
