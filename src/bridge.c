#include "bridge.h"

Value *BridgeFromBoolean(Boolean *boolean) {
    return (Value *)boolean;
}

Value *BridgeFromCase(Case *block) {
    return (Value *)block;
}

Value *BridgeFromDo(Do *block) {
    return (Value *)block;
}

Value *BridgeFromFloat(Float *fpv) {
    return (Value *)fpv;
}

Value *BridgeFromIdentifier(Identifier *id) {
    return (Value *)id;
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

Value *BridgeFromModule(Module *module) {
    return (Value *)module;
}

Value *BridgeFromNil(Nil *nil) {
    return (Value *)nil;
}

Value *BridgeFromRange(Range *range) {
    return (Value *)range;
}

Value *BridgeFromResult(Result *result) {
    return (Value *)result;
}

Value *BridgeFromSet(Set *set) {
    return (Value *)set;
}

Value *BridgeFromString(String *string) {
    return (Value *)string;
}

Value *BridgeFromWhen(When *block) {
    return (Value *)block;
}

Boolean *BridgeToBoolean(Value *booleanValue) {
    return (Boolean *)booleanValue;
}

Case *BridgeToCase(Value *caseValue) {
    return (Case *)caseValue;
}

Do *BridgeToDo(Value *doValue) {
    return (Do *)doValue;
}

Float *BridgeToFloat(Value *floatValue) {
    return (Float *)floatValue;
}

Identifier *BridgeToIdentifier(Value *idValue) {
    return (Identifier *)idValue;
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

Module *BridgeToModule(Value *moduleValue) {
    return (Module *)moduleValue;
}

Nil *BridgeToNil(Value *nilValue) {
    return (Nil *)nilValue;
}

Range *BridgeToRange(Value *rangeValue) {
    return (Range *)rangeValue;
}

Result *BridgeToResult(Value *resultValue) {
    return (Result *)resultValue;
}

Set *BridgeToSet(Value *setValue) {
    return (Set *)setValue;
}

String *BridgeToString(Value *stringValue) {
    return (String *)stringValue;
}

When *BridgeToWhen(Value *whenValue) {
    return (When *)whenValue;
}
