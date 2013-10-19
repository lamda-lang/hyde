#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "runtime.h"

Value *BooleanCreate(Bool truth);
Bool BooleanDecode(Binary *binary, Integer32 *offset, Value **value);
Value *BooleanEqual(Boolean *boolean, Boolean *other);

#endif
