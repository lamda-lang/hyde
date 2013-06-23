#ifndef VALUE_H
#define VALUE_H

#include "api.h"

Type ValueType(Value *value);
void ValueSetFlag(Value *value, Flag mask, bool truth);
bool ValueFlagSet(Value *value, Flag mask);
void ValueEnumerate(Value *value, void (*block)(Value *value));
void ValueDealloc(Value *value);
Integer64 ValueHash(Value *value);
bool ValueEqual(Value *value, Value *other);

#endif
