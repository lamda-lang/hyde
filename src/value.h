#ifndef VALUE_H
#define VALUE_H

#include "runtime.h"

extern Value *VALUE_TRUE;
extern Value *VALUE_FALSE;
extern Value *VALUE_NIL;

void ValueEncode(Value *value, Byte **bytes);
Value *ValueDecode(Byte **bytes, Error *error);
Value *ValueEval(Value *value, Value *context, Error *error);
Bool ValueEqual(Value *value, Value *other);
Value *ValueSetValueForKey(Value *collection, Value *value, Value *key, Error *error);
Value *ValueGetValueForKey(Value *collection, Value *key);
Value *ValueCall(Value *value, Value **args, Integer8 count, Error *error);
Size ValueSize(Value *value);
Size ValueRelease(Value *value);

#endif
