#ifndef FLOAT_H
#define FLOAT_H

#include "runtime.h"

Size FloatSize(Float *fpn);
void FLoatEncode(Float *fpn, Byte **bytes);
Float *FloatDecode(Byte **bytes, Error *error);
Bool FloatEqual(Float *fpn, Float *other);
Size FloatRelease(Float *fpn);

#endif
