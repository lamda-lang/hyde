#ifndef BUILTIN_FLOAT_H
#define BUILTIN_FLOAT_H

#include <runtime.h>

typedef struct Float Float;

Value *FloatDecode(Byte **bytes);
Bool FloatEqual(Float *fpv, Float *other);
Size FloatRelease(Float *fpv);

#endif
