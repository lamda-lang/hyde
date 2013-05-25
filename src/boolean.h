#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "api.h"

Value *BooleanValueBridge(Boolean *boolean);

Boolean *BooleanCreate(bool truth);

void BooleanDealloc(Value *boolean);

Integer64Bit BooleanHash(Value *boolean);

#endif
