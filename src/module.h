#ifndef MODULE_H
#define MODULE_H

#include "runtime.h"

Size ModuleSize(Module *module);
Size ModuleEncode(Module *module, Byte **bytes);
Module *ModuleDecode(Byte **bytes, Error *error);
Module *ModuleEval(Module *module, Value *context, Error *error);
Bool ModuleEqual(Module *module, Module *other);
Size ModuleRelease(Module *module);

#endif
