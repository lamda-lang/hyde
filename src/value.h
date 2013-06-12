#ifndef VALUE_H
#define VALUE_H

#include "api.h"

Type ValueType(Value *value);

void ValueSetFlag(Value *value, Flag mask, bool truth);

bool ValueFlagSet(Value *value, Flag mask);

void ValueEnumerate(Value *value, void (*block)(Value *value));

void ValueDealloc(Value *value);

Integer64 ValueHash(Value *value);

Value *ValueEval(Value *value, bool pure, Error *error);

Boolean *ValueBooleanBridge(Value *value);

Case *ValueCaseBridge(Value *value);

Do *ValueDoBridge(Value *value);

Float *ValueFloatBridge(Value *value);

Identifier *ValueIdentifierBridge(Value *value);

Integer *ValueIntegerBridge(Value *value);

Lambda *ValueLambdaBridge(Value *value);

List *ValueListBridge(Value *value);

Map *ValueMapBridge(Value *value);

Nil *ValueNilBridge(Value *value);

Range *ValueRangeBridge(Value *value);

Result *ValueResultBridge(Value *value);

Set *ValueSetBridge(Value *value);

String *ValueStringBridge(Value *value);

When *ValueWhenBridge(Value *value);

#endif
