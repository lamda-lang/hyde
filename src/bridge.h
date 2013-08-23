#ifndef BRIDGE_H
#define BRIDGE_H

#include "runtime.h"

VALUE *BridgeFromBoolean(Boolean *boolean);
VALUE *BridgeFromCase(Case *block);
VALUE *BridgeFromComprehension(Comprehension *comprehension);
VALUE *BridgeFromDo(Do *block);
VALUE *BridgeFromFloat(Float *fpv);
VALUE *BridgeFromInteger(Integer *integer);
VALUE *BridgeFromLamda(Lamda *lamda);
VALUE *BridgeFromList(List *list);
VALUE *BridgeFromMap(Map *map);
VALUE *BridgeFromNil(Nil *nil);
VALUE *BridgeFromProtocol(Protocol *protocol);
VALUE *BridgeFromRange(Range *range);
VALUE *BridgeFromResult(Result *result);
VALUE *BridgeFromSet(Set *set);
VALUE *BridgeFromString(String *string);
VALUE *BridgeFromToken(Token *token);
VALUE *BridgeFromType(Type *type);
VALUE *BridgeFromVariable(Variable *variable);
VALUE *BridgeFromWhen(When *block);
Boolean *BridgeToBoolean(VALUE *booleanValue);
Case *BridgeToCase(VALUE *caseValue);
Comprehension *BridgeToComprehension(VALUE *comprehensionValue);
Do *BridgeToDo(VALUE *doValue);
Float *BridgeToFloat(VALUE *floatValue);
Integer *BridgeToInteger(VALUE *integerValue);
Lamda *BridgeToLamda(VALUE *lamdaValue);
List *BridgeToList(VALUE *listValue);
Map *BridgeToMap(VALUE *mapValue);
Nil *BridgeToNil(VALUE *nilValue);
Protocol *BridgeToProtocol(VALUE *protocolValue);
Range *BridgeToRange(VALUE *rangeValue);
Result *BridgeToResult(VALUE *resultValue);
Set *BridgeToSet(VALUE *setValue);
String *BridgeToString(VALUE *stringValue);
Token *BridgeToToken(VALUE *tokenValue);
Type *BridgeToType(VALUE *typeValue);
Variable *BridgeToVariable(VALUE *variableValue);
When *BridgeToWhen(VALUE *whenValue);

#endif
