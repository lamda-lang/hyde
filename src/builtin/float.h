#ifndef BUILTIN_FLOAT_H
#define BUILTIN_FLOAT_H

#include <runtime.h>

typedef struct Float Float;

Float *FloatDecode(Byte **bytes);
Value *FloatEqual(Float *fpn, Float *other);
Size FloatRelease(Float *fpn);

#endif
