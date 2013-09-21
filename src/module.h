#ifndef MODULE_H
#define MODULE_H

#include "runtime.h"

Module *ModuleDecode(Byte **bytes);
Module *ModuleEval(Module *module, Value *context);
Bool ModuleEqual(Module *module, Module *other);
Size ModuleRelease(Module *module);

#endif
