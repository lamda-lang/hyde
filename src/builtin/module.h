#ifndef BUILTIN_MODULE_H
#define BUILTIN_MODULE_H

#include <runtime.h>

typedef struct Module Module;

Value *ModuleDecode(Byte **bytes);
Value *ModuleEval(Module *module, Value *context);
Value *ModuleEqual(Module *module, Module *other);
Size ModuleRelease(Module *module);

#endif
