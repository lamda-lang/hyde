#ifndef VALUE_H
#define VALUE_H

#include "api.h"

Type ValueType(Value *value);

void ValueSetFlag(Value *value, Flag mask, bool truth);

bool ValueFlagSet(Value *value, Flag mask);

void ValueEnumerate(Value *value, void (*block)(Value *value));

void ValueDealloc(Value *value);

Integer64 ValueHash(Value *value);

Boolean *ValueBooleanBridge(Value *value);

Identifier *ValueIdentifierBridge(Value *value);

Integer *ValueIntegerBridge(Value *value);

Lambda *ValueLambdaBridge(Value *value);

List *ValueListBridge(Value *value);

Map *ValueMapBridge(Value *value);

Nil *ValueNilBridge(Value *value);

String *ValueStringBridge(Value *value);

#endif
