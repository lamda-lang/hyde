#ifndef BUILTIN_MODULE_H
#define BUILTIN_MODULE_H

#include <runtime.h>

Value *ModuleDecode(Byte **bytes);
Bool ModuleEqual(void *moduleData, void *otherData);
void ModuleRelease(void *moduleData);

#endif
