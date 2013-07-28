#include "bridge.h"

Value *BridgeFromBoolean(Boolean *boolean) {
    return (Value *)boolean;
}

Value *BridgeFromDo(Do *block) {
    return (Value *)block;
}

Value *BridgeFromFloat(Float *fpv) {
    return (Value *)fpv;
}

Value *BridgeFromToken(Token *token) {
    return (Value *)token;
}

Value *BridgeFromInteger(Integer *integer) {
    return (Value *)integer;
}

Value *BridgeFromLamda(Lamda *lamda) {
    return (Value *)lamda;
}

Value *BridgeFromList(List *list) {
    return (Value *)list;
}

Value *BridgeFromMap(Map *map) {
    return (Value *)map;
}

Value *BridgeFromNil(Nil *nil) {
    return (Value *)nil;
}

Value *BridgeFromRange(Range *range) {
    return (Value *)range;
}

Value *BridgeFromSet(Set *set) {
    return (Value *)set;
}

Value *BridgeFromString(String *string) {
    return (Value *)string;
}

Boolean *BridgeToBoolean(Value *booleanValue) {
    return (Boolean *)booleanValue;
}

Do *BridgeToDo(Value *doValue) {
    return (Do *)doValue;
}

Float *BridgeToFloat(Value *floatValue) {
    return (Float *)floatValue;
}

Token *BridgeToToken(Value *tokenValue) {
    return (Token *)tokenValue;
}

Integer *BridgeToInteger(Value *integerValue) {
    return (Integer *)integerValue;
}

Lamda *BridgeToLamda(Value *lamdaValue) {
    return (Lamda *)lamdaValue;
}

List *BridgeToList(Value *listValue) {
    return (List *)listValue;
}

Map *BridgeToMap(Value *mapValue) {
    return (Map *)mapValue;
}

Nil *BridgeToNil(Value *nilValue) {
    return (Nil *)nilValue;
}

Range *BridgeToRange(Value *rangeValue) {
    return (Range *)rangeValue;
}

Set *BridgeToSet(Value *setValue) {
    return (Set *)setValue;
}

String *BridgeToString(Value *stringValue) {
    return (String *)stringValue;
}
