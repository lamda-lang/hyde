#ifndef BRIDGE_H
#define BRIDGE_H

#include "api.h"

Value *BridgeFromBoolean(Boolean *boolean);
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
Value *BridgeFromSet(Set *set);
Value *BridgeFromString(String *string);
Boolean *BridgeToBoolean(Value *booleanValue);
Do *BridgeToDo(Value *doValue);
Float *BridgeToFloat(Value *floatValue);
Identifier *BridgeToIdentifier(Value *idValue);
Integer *BridgeToInteger(Value *integerValue);
Lamda *BridgeToLamda(Value *lamdaValue);
List *BridgeToList(Value *listValue);
Map *BridgeToMap(Value *mapValue);
Module *BridgeToModule(Value *moduleValue);
Nil *BridgeToNil(Value *nilValue);
Range *BridgeToRange(Value *rangeValue);
Set *BridgeToSet(Value *setValue);
String *BridgeToString(Value *stringValue);

#endif
