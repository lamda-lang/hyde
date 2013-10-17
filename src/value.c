#include "value.h"

enum {
    BINARY = 0,
    BOOLEAN = 1,
    CASE = 2,
    DO = 3,
    FLOAT = 4,
    IDENTIFIER = 5,
    INTEGER = 6,
    LAMDA = 7,
    LIST = 8,
    MAP = 9,
    MODULE = 10,
    NIL = 11,
    RANGE = 12,
    RESULT = 13,
    SET = 14,
    STRING = 15,
    TOKEN = 16,
    TYPE = 17,
    WHEN = 18
};

struct Value {
    void *primitive;
    Integer8 type;
};

Bool ValueEval(Value *value, Stack *stack) {
    StackPushValue(stack, value);
    switch (value->type) {
    case LIST:
        return ListEval(value->primitive, stack);
    default:
        return TRUE;
    }
}

static Value *ValueCreate(Integer8 type, void *primitive) {
    Value *value = MemoryAllocUnit(sizeof(Value));
    value->type = type;
    value->primitive = primitive;
    return value;
}

static void *ValuePrimitive(Value *value, Integer8 type) {
    if (value->type != type)
        abort();
    return value->primitive;
}

Value *ValueCreateBinary(Binary *binary) {
    return ValueCreate(BINARY, binary);
}

Value *ValueCreateBoolean(Boolean *boolean) {
    return ValueCreate(BOOLEAN, boolean);
}

Value *ValueCreateCase(Case *block) {
    return ValueCreate(CASE, block);
}

Value *ValueCreateDo(Do *block) {
    return ValueCreate(DO, block);
}

Value *ValueCreateFloat(Float *fpn) {
    return ValueCreate(FLOAT, fpn);
}

Value *ValueCreateIdentifier(Identifier *id) {
    return ValueCreate(IDENTIFIER, id);
}

Value *ValueCreateInteger(Integer *integer) {
    return ValueCreate(INTEGER, integer);
}

Value *ValueCreateLamda(Lamda *lamda) {
    return ValueCreate(LAMDA, lamda);
}

Value *ValueCreateList(List *list) {
    return ValueCreate(LIST, list);
}

Value *ValueCreateMap(Map *map) {
    return ValueCreate(MAP, map);
}

Value *ValueCreateModule(Module *module) {
    return ValueCreate(MODULE, module);
}

Value *ValueCreateNil(Nil *nil) {
    return ValueCreate(NIL, nil);
}

Value *ValueCreateRange(Range *range) {
    return ValueCreate(RANGE, range);
}

Value *ValueCreateResult(Result *result) {
    return ValueCreate(RESULT, result);
}

Value *ValueCreateSet(Set *set) {
    return ValueCreate(SET, set);
}

Value *ValueCreateString(String *string) {
    return ValueCreate(STRING, string);
}

Value *ValueCreateToken(Token *token) {
    return ValueCreate(TOKEN, token);
}

Value *ValueCreateType(Type *type) {
    return ValueCreate(TYPE, type);
}

Value *ValueCreateWhen(When *block) {
    return ValueCreate(WHEN, block);
}

Binary *ValueBinaryPrimitive(Value *value) {
    return ValuePrimitive(value, BINARY);
}

Boolean *ValueBooleanPrimitive(Value *value) {
    return ValuePrimitive(value, BOOLEAN);
}

Case *ValueCasePrimitive(Value *value) {
    return ValuePrimitive(value, CASE);
}

Do *ValueDoPrimitive(Value *value) {
    return ValuePrimitive(value, DO);
}

Float *ValueFloatPrimitive(Value *value) {
    return ValuePrimitive(value, FLOAT);
}

Identifier *ValueIdentifierPrimitive(Value *value) {
    return ValuePrimitive(value, IDENTIFIER);
}

Integer *ValueIntegerPrimitive(Value *value) {
    return ValuePrimitive(value, INTEGER);
}

Lamda *ValueLamdaPrimitive(Value *value) {
    return ValuePrimitive(value, LAMDA);
}

List *ValueListPrimitive(Value *value) {
    return ValuePrimitive(value, LIST);
}

Map *ValueMapPrimitive(Value *value) {
    return ValuePrimitive(value, MAP);
}

Module *ValueModulePrimitive(Value *value) {
    return ValuePrimitive(value, MODULE);
}

Nil *ValueNilPrimitive(Value *value) {
    return ValuePrimitive(value, NIL);
}

Range *ValueRangePrimitive(Value *value) {
    return ValuePrimitive(value, RANGE);
}

Result *ValueResultPrimitive(Value *value) {
    return ValuePrimitive(value, RESULT);
}

Set *ValueSetPrimitive(Value *value) {
    return ValuePrimitive(value, SET);
}

String *ValueStringPrimitive(Value *value) {
    return ValuePrimitive(value, STRING);
}

Token *ValueTokenPrimitive(Value *value) {
    return ValuePrimitive(value, TOKEN);
}

Type *ValueTypePrimitive(Value *value) {
    return ValuePrimitive(value, TYPE);
}

When *ValueWhenPrimitive(Value *value) {
    return ValuePrimitive(value, WHEN);
}
