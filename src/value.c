#include "value.h"

enum {
    BINARY = 0,
    BOOLEAN = 1,
    CASE = 2,
    DO = 3,
    EXCEPTION = 4,
    FLOAT = 5,
    IDENTIFIER = 6,
    INTEGER = 7,
    LAMDA = 8,
    LIST = 9,
    MAP = 10,
    MODULE = 11,
    NIL = 12,
    RESULT = 13,
    SET = 14,
    STRING = 15,
    TOKEN = 16,
    WHEN = 17
};

struct Value {
    void *primitive;
    Integer8 type;
};

static Value *ValueCreate(Integer8 type, void *primitive) {
    Value *value = MemoryAllocUnit(sizeof(Value));
    value->type = type;
    value->primitive = primitive;
    return value;
}

static void *ValuePrimitive(Value *value, Integer8 type) {
    if (value->type != type)
        return NULL;
    return value->primitive;
}

Bool ValueEval(Value *value, Context *context, Stack *stack) {
    StackPushValue(stack, value);
    switch (value->type) {
    case CASE:
        return CaseEval(value->primitive, context, stack);
    case EXCEPTION:
        return FALSE;
    case IDENTIFIER:
        return IdentifierEval(value->primitive, context, stack);
    case LAMDA:
        return LamdaEval(value->primitive, context, stack);
    case LIST:
        return ListEval(value->primitive, context, stack);
    case MAP:
        return MapEval(value->primitive, context, stack);
    case MODULE:
        return ModuleEval(value->primitive, context, stack);
    case RESULT:
        return ResultEval(value->primitive, context, stack);
    case SET:
        return SetEval(value->primitive, context, stack);
    case WHEN:
        return WhenEval(value->primitive, context, stack);
    default:
        return TRUE;
    }
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

Value *ValueCreateException(Exception *exception) {
    return ValueCreate(EXCEPTION, exception);
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

When *ValueWhenPrimitive(Value *value) {
    return ValuePrimitive(value, WHEN);
}
