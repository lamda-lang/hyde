#ifndef BRIDGE_H
#define BRIDGE_H

#include "api.h"

Value *BridgeFromBoolean(Boolean *boolean);
Value *BridgeFromCase(Case *block);
Value *BridgeFromDo(Do *block);
Value *BridgeFromFloat(Float *fpv);
Value *BridgeFromIdentifier(Identifier *id);
Value *BridgeFromInteger(Integer *integer);
Value *BridgeFromLamda(Lamda *lamda);
Value *BridgeFromList(List *list);
Value *BridgeFromMap(Map *map);
Value *BridgeFromModule(Module *module);
Value *BridgeFromNil(Nil *nil);
Value *BridgeFromRange(Range *range);
Value *BridgeFromResult(Result *result);
Value *BridgeFromSet(Set *set);
Value *BridgeFromString(String *string);
Value *BridgeFromWhen(When *block);
Boolean *BridgeToBoolean(Value *booleanValue);
Case *BridgeToCase(Value *caseValue);
Do *BridgeToDo(Value *doValue);
Float *BridgeToFloat(Value *floatValue);
Identifier *BridgeToIdenfier(Value *idValue);
Integer *BridgeToInteger(Value *integerValue);
Lamda *BridgeToLamda(Value *lamdaValue);
List *BridgeToList(Value *listValue);
Map *BridgeToMap(Value *mapValue);
Module *BridgeToModule(Value *moduleValue);
Nil *BridgeToNil(Value *nilValue);
Range *BridgeToRange(Value *rangeValue);
Result *BridgeToResult(Value *resultValue);
Set *BridgeToSet(Value *setValue);
String *BridgeToString(Value *stringValue);
When *BridgeToWhen(Value *whenValue);

#endif
