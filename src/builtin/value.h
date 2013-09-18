#ifndef BUILTIN_VALUE_H
#define BUILTIN_VALUE_H

#include <runtime.h>

Value *ValueDecode(Byte **bytes);
Value *ValueEval(Value *value, Value *context);
Bool ValueEqual(Value *value, Value *other);
Value *ValueSetValueForKey(Value *collection, Value *value, Value *key);
Value *ValueGetValueForKey(Value *collection, Value *key);
Value *ValueCall(Value *value, Value **args, Integer8 count);
Size ValueRelease(Value *value);

extern Value *VALUE_TRUE;
extern Value *VALUE_FALSE;
extern Value *VALUE_NIL;

#endif
