#ifndef BUILTIN_VALUE_H
#define BUILTIN_VALUE_H

#include <runtime.h>

Value *ValueCreate(Builtin builtin, void *model, Error *error);
Bool ValueEqual(Value *value, Value *other);

#endif
