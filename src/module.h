#ifndef MODULE_H
#define MODULE_H

#include "api.h"

void ModuleDealloc(Value *moduleValue);
Value *ModuleGetValueForIdentifier(Value *moduleValue, Value *idValue);

#endif
