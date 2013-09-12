#ifndef BUILTIN_FLOAT_H
#define BUILTIN_FLOAT_H

#include <runtime.h>

Value *FloatDecode(Byte **bytes);
Bool FloatEqual(Float *fpv, Float *other);
void FloatRelease(Float *fpv);

#endif
