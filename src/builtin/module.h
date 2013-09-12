#ifndef BUILTIN_MODULE_H
#define BUILTIN_MODULE_H

#include <runtime.h>

Value *ModuleDecode(Byte **bytes);
Bool ModuleEqual(Module *module, Module *other);
void ModuleRelease(Module *module);

#endif
