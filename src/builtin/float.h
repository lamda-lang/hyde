#ifndef BUILTIN_FLOAT_H
#define BUILTIN_FLOAT_H

#include <runtime.h>

Value *FloatDecode(Byte **bytes, Error *error);
Bool FloatEqual(void *floatModel, void *otherModel);
void FloatRelease(void *floatModel);

#endif
