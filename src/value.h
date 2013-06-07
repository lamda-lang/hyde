#ifndef VALUE_H
#define VALUE_H

#include "api.h"

void ValueSetFlag(Value *value, Flag mask, bool truth);

bool ValueFlagSet(Value *value, Flag mask);

void ValueEnumerate(Value *value, void (*block)(Value *value));

void ValueDealloc(Value *value);

Integer64 ValueHash(Value *value);

Boolean *ValueBooleanBridge(Value *value, Error *error);

Do *ValueDoBridge(Value *value, Error *error);

Float *ValueFloatBridge(Value *value, Error *error);

Identifier *ValueIdentifierBridge(Value *value, Error *error);

Integer *ValueIntegerBridge(Value *value, Error *error);

Lambda *ValueLambdaBridge(Value *value, Error *error);

List *ValueListBridge(Value *value, Error *error);

Map *ValueMapBridge(Value *value, Error *error);

Nil *ValueNilBridge(Value *value, Error *error);

Range *ValueRangeBridge(Value *value, Error *error);

Result *ValueResultBridge(Value *value, Error *error);

Set *ValueSetBridge(Value *value, Error *error);

String *ValueStringBridge(Value *value, Error *error);

#endif
