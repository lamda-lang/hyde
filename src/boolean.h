#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "runtime.h"

Value *BooleanCreate(Bool truth);
Bool BooleanTruth(Boolean *boolean);
Bool BooleanDecode(Binary *binary, Integer32 *offset, Value **value);
Bool BooleanEqual(Boolean *boolean, Boolean *other);

#endif
