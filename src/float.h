#ifndef FLOAT_H
#define FLOAT_H

#include "runtime.h"

Size FloatSize(Float *fpn);
Size FloatEncode(Float *fpn, Byte **bytes);
Float *FloatDecode(Byte **bytes, Error *error);
Value *FloatEval(Value *value, Float *fpn, Value *context, Error *error);
Bool FloatEqual(Float *fpn, Float *other);
Size FloatRelease(Float *fpn);

#endif
