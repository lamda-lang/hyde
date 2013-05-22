#ifndef VALUE_H
#define VALUE_H

#include "runtime.h"

Value ValueInit(Type type, Flag mask);

Type ValueType(Value *value);

void ValueSetFlag(Value *value, Flag mask, bool truth);

bool ValueFlagSet(Value *value, Flag mask);

bool ValueBaseFlagSet(Value value, Flag mask);

Boolean *ValueBooleanBridge(Value *value);

Identifier *ValueIdentifierBridge(Value *value);

Integer *ValueIntegerBridge(Value *value);

Lambda *ValueLambdaBridge(Value *value);

List *ValueListBridge(Value *value);

Map *ValueMapBridge(Value *value);

Nil *ValueNilBridge(Value *value);

String *ValueStringBridge(Value *value);

void ValueEnumerate(Value *value, void (*block)(Value *value));

void ValueDealloc(Value *value);

Integer64Bit ValueHash(Value *value);

#endif
