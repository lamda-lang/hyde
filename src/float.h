#ifndef FLOAT_H
#define FLOAT_H

#include "runtime.h"

Bool FloatDecode(Binary *binary, Integer32 *offset, Value **value);
Value *FloatEqual(Float *fpn, Float *other);

#endif
