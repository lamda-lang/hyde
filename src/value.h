#ifndef VALUE_H
#define VALUE_H

#include "runtime.h"

extern Value *VALUE_TRUE;
extern Value *VALUE_FALSE;
extern Value *VALUE_NIL;

Value *ValueDecode(Byte **bytes);
Value *ValueEval(Value *value, Value *context);
Bool ValueEqual(Value *value, Value *other);
Value *ValueSetValueForKey(Value *collection, Value *value, Value *key);
Value *ValueGetValueForKey(Value *collection, Value *key);
Value *ValueCall(Value *value, Value **args, Integer8 count);
Size ValueRelease(Value *value);

#endif
