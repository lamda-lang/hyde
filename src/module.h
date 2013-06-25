#ifndef MODULE_H
#define MODULE_H

#include "api.h"

void *ModuleDecode(Byte **bytes, Error *error);
Value *ModuleEval(void *data, Code *code, Value **context, bool pure, Error *error);
Value *ModuleCreate(Integer32 count, Error *error);
void ModuleDealloc(Value *moduleValue);
Value *ModuleGetValueForIdentifier(Value *moduleValue, Value *idValue);

#endif
