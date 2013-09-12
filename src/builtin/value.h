#ifndef BUILTIN_VALUE_H
#define BUILTIN_VALUE_H

#include <runtime.h>

Value *ValueCreate(Model model, void *data);
Bool ValueEqual(Value *value, Value *other);
Value *ValueDecode(Byte **bytes);

#endif
