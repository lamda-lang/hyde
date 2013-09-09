#ifndef BUILTIN_VALUE_H
#define BUILTIN_VALUE_H

#include <runtime.h>

Value *ValueCreate(Builtin builtin, void *model, Error *error);

#endif
