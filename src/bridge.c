#include "bridge.h"

VALUE *BridgeFromBoolean(Boolean *boolean) {
    return (VALUE *)boolean;
}

VALUE *BridgeFromCase(Case *block) {
    return (VALUE *)block;
}

VALUE *BridgeFromComprehension(Comprehension *comprehension) {
    return (VALUE *)comprehension;
}

VALUE *BridgeFromDo(Do *block) {
    return (VALUE *)block;
}

VALUE *BridgeFromFloat(Float *fpv) {
    return (VALUE *)fpv;
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

VALUE *BridgeFromProtocol(Protocol *protocol) {
    return (VALUE *)protocol;
}

VALUE *BridgeFromRange(Range *range) {
    return (VALUE *)range;
}

VALUE *BridgeFromResult(Result *result) {
    return (VALUE *)result;
}

VALUE *BridgeFromSet(Set *set) {
    return (VALUE *)set;
}

VALUE *BridgeFromString(String *string) {
    return (VALUE *)string;
}

VALUE *BridgeFromToken(Token *token) {
    return (VALUE *)token;
}

VALUE *BridgeFromType(Type *type) {
    return (VALUE *)type;
}

VALUE *BridgeFromVariable(Variable *variable) {
    return (VALUE *)variable;
}

VALUE *BridgeFromWhen(When *block) {
    return (VALUE *)block;
}

Boolean *BridgeToBoolean(VALUE *booleanValue) {
    return (Boolean *)booleanValue;
}

Case *BridgeToCase(VALUE *caseValue) {
    return (Case *)caseValue;
}

Comprehension *BridgeToComprehension(VALUE *comprehensionValue) {
    return (Comprehension *)comprehensionValue;
}

Do *BridgeToDo(VALUE *doValue) {
    return (Do *)doValue;
}

Float *BridgeToFloat(VALUE *floatValue) {
    return (Float *)floatValue;
}

Integer *BridgeToInteger(VALUE *integerValue) {
    return (Integer *)integerValue;
}

Lamda *BridgeToLamda(VALUE *lamdaValue) {
    return (Lamda *)lamdaValue;
}

List *BridgeToList(VALUE *listValue) {
    return (List *)listValue;
}

Map *BridgeToMap(VALUE *mapValue) {
    return (Map *)mapValue;
}

Nil *BridgeToNil(VALUE *nilValue) {
    return (Nil *)nilValue;
}

Protocol *BridgeToProtocol(VALUE *protocolValue) {
    return (Protocol *)protocolValue;
}

Range *BridgeToRange(VALUE *rangeValue) {
    return (Range *)rangeValue;
}

Result *BridgeToResult(VALUE *resultValue) {
    return (Result *)resultValue;
}

Set *BridgeToSet(VALUE *setValue) {
    return (Set *)setValue;
}

String *BridgeToString(VALUE *stringValue) {
    return (String *)stringValue;
}

Token *BridgeToToken(VALUE *tokenValue) {
    return (Token *)tokenValue;
}

Type *BridgeToType(VALUE *typeValue) {
    return (Type *)typeValue;
}

Variable *BridgeToVariable(VALUE *variableValue) {
    return (Variable *)variableValue;
}

When *BridgeToWhen(VALUE *whenValue) {
    return (When *)whenValue;
}
