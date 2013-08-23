#include "bridge.h"

VALUE *BridgeFromBoolean(Boolean *boolean) {
    return (VALUE *)boolean;
}

VALUE *BridgeFromDo(Do *block) {
    return (VALUE *)block;
}

VALUE *BridgeFromFloat(Float *fpv) {
    return (VALUE *)fpv;
}

VALUE *BridgeFromToken(Token *token) {
    return (VALUE *)token;
}

VALUE *BridgeFromInteger(Integer *integer) {
    return (VALUE *)integer;
}

VALUE *BridgeFromLamda(Lamda *lamda) {
    return (VALUE *)lamda;
}

VALUE *BridgeFromList(List *list) {
    return (VALUE *)list;
}

VALUE *BridgeFromMap(Map *map) {
    return (VALUE *)map;
}

VALUE *BridgeFromNil(Nil *nil) {
    return (VALUE *)nil;
}

VALUE *BridgeFromRange(Range *range) {
    return (VALUE *)range;
}

VALUE *BridgeFromSet(Set *set) {
    return (VALUE *)set;
}

VALUE *BridgeFromString(String *string) {
    return (VALUE *)string;
}

Boolean *BridgeToBoolean(VALUE *booleanVALUE) {
    return (Boolean *)booleanVALUE;
}

Do *BridgeToDo(VALUE *doVALUE) {
    return (Do *)doVALUE;
}

Float *BridgeToFloat(VALUE *floatVALUE) {
    return (Float *)floatVALUE;
}

Token *BridgeToToken(VALUE *tokenVALUE) {
    return (Token *)tokenVALUE;
}

Integer *BridgeToInteger(VALUE *integerVALUE) {
    return (Integer *)integerVALUE;
}

Lamda *BridgeToLamda(VALUE *lamdaVALUE) {
    return (Lamda *)lamdaVALUE;
}

List *BridgeToList(VALUE *listVALUE) {
    return (List *)listVALUE;
}

Map *BridgeToMap(VALUE *mapVALUE) {
    return (Map *)mapVALUE;
}

Nil *BridgeToNil(VALUE *nilVALUE) {
    return (Nil *)nilVALUE;
}

Range *BridgeToRange(VALUE *rangeVALUE) {
    return (Range *)rangeVALUE;
}

Set *BridgeToSet(VALUE *setVALUE) {
    return (Set *)setVALUE;
}

String *BridgeToString(VALUE *stringVALUE) {
    return (String *)stringVALUE;
}
