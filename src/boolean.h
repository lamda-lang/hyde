#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "runtime.h"

Value *BooleanValueBridge(Boolean *boolean);

Boolean *BooleanCreate(bool truth);

void BooleanDealloc(Value *boolean_Boolean);

Integer64Bit BooleanHash(Value *boolean_Boolean);

#endif
