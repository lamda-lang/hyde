#ifndef MODULE_H
#define MODULE_H

#include "api.h"

Value *ModuleDecode(Byte **bytes, Error *error);

void ModuleDealloc(Value *moduleValue);

void ModuleFetch(Value *moduleValue, Value **values);

Value *ModuleGetValueForIdentifier(Value *moduleValue, Value *idValue);

Value *ModuleEval(Value *moduleValue, bool pure, Error *error);

Value *ModuleWithID(Char *path);

Status ModuleLoad(Char *path, Error *error);

#endif
