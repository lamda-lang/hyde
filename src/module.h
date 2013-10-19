#ifndef MODULE_H
#define MODULE_H

#include "runtime.h"

Bool ModuleDecode(Binary *binary, Integer32 *offset, Value **value);
Bool ModuleEval(Module *module, Context *context, Stack *stack);

#endif
