#include "value.h"

enum {
    MODEL_BINARY = 0,
    MODEL_BOOLEAN = 1,
    MODEL_CASE = 2,
    MODEL_DO = 3,
    MODEL_FLOAT = 4,
    MODEL_IDENTIFIER = 5,
    MODEL_INTEGER = 6,
    MODEL_LAMDA = 7,
    MODEL_LIST = 8,
    MODEL_MAP = 9,
    MODEL_MODULE = 10,
    MODEL_NIL = 11,
    MODEL_RANGE = 12,
    MODEL_RESULT = 13,
    MODEL_SET = 14,
    MODEL_STRING = 15,
    MODEL_TOKEN = 16,
    MODEL_TYPE = 17,
    MODEL_WHEN = 18
};

struct Value {
    void *primitive;
    Integer8 model;
};

static Value *ValueCreate(Integer8 model, void *primitive) {
    Value *value = MemoryAllocUnit(sizeof(Value));
    value->model = model;
    value->primitive = primitive;
    return value;
}

static void *ValuePrimitive(Value *value, Integer8 model) {
    if (value->model != model)
        abort();
    return value->primitive;
}

Value *ValueCreateBinary(Binary *binary) {
    return ValueCreate(MODEL_BINARY, binary);
}

Value *ValueCreateBoolean(Boolean *boolean) {
    return ValueCreate(MODEL_BOOLEAN, boolean);
}

Value *ValueCreateCase(Case *block) {
    return ValueCreate(MODEL_CASE, block);
}

Value *ValueCreateDo(Do *block) {
    return ValueCreate(MODEL_DO, block);
}

Value *ValueCreateFloat(Float *fpn) {
    return ValueCreate(MODEL_FLOAT, fpn);
}

Value *ValueCreateIdentifier(Identifier *id) {
    return ValueCreate(MODEL_IDENTIFIER, id);
}

Value *ValueCreateInteger(Integer *integer) {
    return ValueCreate(MODEL_INTEGER, integer);
}

Value *ValueCreateLamda(Lamda *lamda) {
    return ValueCreate(MODEL_LAMDA, lamda);
}

Value *ValueCreateList(List *list) {
    return ValueCreate(MODEL_LIST, list);
}

Value *ValueCreateMap(Map *map) {
    return ValueCreate(MODEL_MAP, map);
}

Value *ValueCreateModule(Module *module) {
    return ValueCreate(MODEL_MODULE, module);
}

Value *ValueCreateNil(Nil *nil) {
    return ValueCreate(MODEL_NIL, nil);
}

Value *ValueCreateRange(Range *range) {
    return ValueCreate(MODEL_RANGE, range);
}

Value *ValueCreateResult(Result *result) {
    return ValueCreate(MODEL_RESULT, result);
}

Value *ValueCreateSet(Set *set) {
    return ValueCreate(MODEL_SET, set);
}

Value *ValueCreateString(String *string) {
    return ValueCreate(MODEL_STRING, string);
}

Value *ValueCreateToken(Token *token) {
    return ValueCreate(MODEL_TOKEN, token);
}

Value *ValueCreateType(Type *type) {
    return ValueCreate(MODEL_TYPE, type);
}

Value *ValueCreateWhen(When *block) {
    return ValueCreate(MODEL_WHEN, block);
}

Binary *ValueBinaryPrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_BINARY);
}

Boolean *ValueBooleanPrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_BOOLEAN);
}

Case *ValueCasePrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_CASE);
}

Do *ValueDoPrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_DO);
}

Float *ValueFloatPrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_FLOAT);
}

Identifier *ValueIdentifierPrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_IDENTIFIER);
}

Integer *ValueIntegerPrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_INTEGER);
}

Lamda *ValueLamdaPrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_LAMDA);
}

List *ValueListPrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_LIST);
}

Map *ValueMapPrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_MAP);
}

Module *ValueModulePrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_MODULE);
}

Nil *ValueNilPrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_NIL);
}

Range *ValueRangePrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_RANGE);
}

Result *ValueResultPrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_RESULT);
}

Set *ValueSetPrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_SET);
}

String *ValueStringPrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_STRING);
}

Token *ValueTokenPrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_TOKEN);
}

Type *ValueTypePrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_TYPE);
}

When *ValueWhenPrimitive(Value *value) {
    return ValuePrimitive(value, MODEL_WHEN);
}
