#ifndef BUILTIN_FLOAT_H
#define BUILTIN_FLOAT_H

#include <runtime.h>

Value *FloatDecode(Byte **bytes);
Bool FloatEqual(void *floatData, void *otherData);
void FloatRelease(void *floatData);

#endif
