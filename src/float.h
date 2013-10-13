#ifndef FLOAT_H
#define FLOAT_H

#include "runtime.h"

Value *FloatDecode(Binary *binary, Integer32 *offset);
Value *FloatEqual(Float *fpn, Float *other);

#endif
