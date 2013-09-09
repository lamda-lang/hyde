#ifndef BUILTIN_INTEGER_H
#define BUILTIN_INTEGER_H

#include <runtime.h>

Value *IntegerDecode(Byte **bytes, Error *error);
Bool IntegerEqual(void *integerModel, void *otherModel);
void IntegerRelease(void *integerModel);

#endif
