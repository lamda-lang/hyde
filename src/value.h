#ifndef VALUE_H
#define VALUE_H

#include "api.h"

Type ValueType(Value *value);

void ValueSetFlag(Value *value, Flag mask, bool truth);

bool ValueFlagSet(Value *value, Flag mask);

void ValueEnumerate(Value *value, void (*block)(Value *value));

void ValueDealloc(Value *value);

Integer64 ValueHash(Value *value);

Boolean *ValueBooleanBridge(Value *booleanValue);

Identifier *ValueIdentifierBridge(Value *idValue);

Integer *ValueIntegerBridge(Value *integerValue);

Lambda *ValueLambdaBridge(Value *lambdaValue);

List *ValueListBridge(Value *listValue);

Map *ValueMapBridge(Value *mapValue);

Nil *ValueNilBridge(Value *nilValue);

String *ValueStringBridge(Value *stringValue);

#endif
