#ifndef MODULE_H
#define MODULE_H

#include "api.h"

Value *ModuleValueBridge(Module *module);

Value *ModuleDecode(Byte **bytes, Error *error);

void ModuleDealloc(Value *moduleValue);

void ModuleFetch(Value *moduleValue, Value **values);

Value *ModuleEval(Value *moduleValue, bool pure, Error *error);

Module *ModuleWithID(String *id);

Status ModuleLoad(String *path, Error *error);

#endif
