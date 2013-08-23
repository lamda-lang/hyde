#ifndef BRIDGE_H
#define BRIDGE_H

#include "api.h"

VALUE *BridgeFromBoolean(Boolean *boolean);
VALUE *BridgeFromDo(Do *block);
VALUE *BridgeFromFloat(Float *fpv);
VALUE *BridgeFromToken(Token *token);
VALUE *BridgeFromInteger(Integer *integer);
VALUE *BridgeFromLamda(Lamda *lamda);
VALUE *BridgeFromList(List *list);
VALUE *BridgeFromMap(Map *map);
VALUE *BridgeFromNil(Nil *nil);
VALUE *BridgeFromRange(Range *range);
VALUE *BridgeFromSet(Set *set);
VALUE *BridgeFromString(String *string);
Boolean *BridgeToBoolean(VALUE *booleanVALUE);
Do *BridgeToDo(VALUE *doVALUE);
Float *BridgeToFloat(VALUE *floatVALUE);
Token *BridgeToToken(VALUE *tokenVALUE);
Integer *BridgeToInteger(VALUE *integerVALUE);
Lamda *BridgeToLamda(VALUE *lamdaVALUE);
List *BridgeToList(VALUE *listVALUE);
Map *BridgeToMap(VALUE *mapVALUE);
Nil *BridgeToNil(VALUE *nilVALUE);
Range *BridgeToRange(VALUE *rangeVALUE);
Set *BridgeToSet(VALUE *setVALUE);
String *BridgeToString(VALUE *stringVALUE);

#endif
