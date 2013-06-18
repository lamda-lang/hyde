#ifndef VALUE_H
#define VALUE_H

#include "api.h"

Type ValueType(Value *value);

void ValueSetFlag(Value *value, Flag mask, bool truth);

bool ValueFlagSet(Value *value, Flag mask);

void ValueEnumerate(Value *value, void (*block)(Value *value));

void ValueDealloc(Value *value);

void ValueFetch(Value *value, Value **values);

Integer64 ValueHash(Value *value);

Value *ValueEval(Value *value, bool pure, Error *error);

Boolean *ValueBooleanBridge(Value *booleanValue);

Case *ValueCaseBridge(Value *caseValue);

Do *ValueDoBridge(Value *doValue);

Float *ValueFloatBridge(Value *floatValue);

Identifier *ValueIdentifierBridge(Value *idValue);

Integer *ValueIntegerBridge(Value *integerValue);

Lambda *ValueLambdaBridge(Value *lambdaValue);

List *ValueListBridge(Value *listValue);

Map *ValueMapBridge(Value *mapValue);

Nil *ValueNilBridge(Value *nilValue);

Range *ValueRangeBridge(Value *rangeValue);

Result *ValueResultBridge(Value *resultValue);

Set *ValueSetBridge(Value *setValue);

String *ValueStringBridge(Value *stringValue);

Module *ValueModuleBridge(Value *moduleValue);

When *ValueWhenBridge(Value *whenValue);

#endif
