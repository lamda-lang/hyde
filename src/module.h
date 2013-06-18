#ifndef MODULE_H
#define MODULE_H

#include "api.h"

Value *ModuleValueBridge(Module *module);

Value *ModuleDecode(Byte **bytes, Error *error);

void ModuleDealloc(Value *moduleValue);

void ModuleFetch(Value *moduleValue, Value **values);

Value *ModuleGetValueForIdentifier(Module *module, Identifier *id);

Value *ModuleEval(Value *moduleValue, bool pure, Error *error);

Module *ModuleWithID(Char *path);

Status ModuleLoad(Char *path, Error *error);

#endif
