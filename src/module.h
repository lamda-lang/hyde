#ifndef MODULE_H
#define MODULE_H

#include "api.h"

Value *ModuleDecode(Byte **bytes, Error *error);

Value *ModuleEval(Value *moduleValue, bool pure, Error *error);

#endif
