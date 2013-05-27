#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "api.h"

Value *BooleanValueBridge(Boolean *boolean);

Boolean *BooleanTrueSingleton(void);

Boolean *BooleanFalseSingleton(void);

Integer64 BooleanHash(Value *booleanValue);

#endif
