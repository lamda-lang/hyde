#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "runtime.h"

Value *BooleanCreate(Bool truth);
Value *BooleanDecode(Binary *binary, Integer32 *offset);
Value *BooleanEqual(Boolean *boolean, Boolean *other);

#endif
