#ifndef BUILTIN_MODULE_H
#define BUILTIN_MODULE_H

#include <runtime.h>

typedef struct Module Module;

Module *ModuleDecode(Byte **bytes);
Module *ModuleEval(Module *module, Value *context);
Bool ModuleEqual(Module *module, Module *other);
Size ModuleRelease(Module *module);

#endif
