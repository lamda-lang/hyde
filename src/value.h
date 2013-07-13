#ifndef VALUE_H
#define VALUE_H

#include "api.h"

Type ValueType(Value *value);
void ValueSetFlag(Value *value, Flag mask, Bool truth);
Bool ValueFlagSet(Value *value, Flag mask);
void ValueEnumerate(Value *value, void (*block)(Value *value));
void ValueDealloc(Value *value);
Integer64 ValueHash(Value *value);
Bool ValueEqual(Value *value, Value *other);

#endif
