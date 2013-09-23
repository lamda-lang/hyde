#include "value.h"

enum {
    OPCODE_BOOLEAN_TRUE = 0,
    OPCODE_BOOLEAN_FALSE = 1,
    OPCODE_CASE = 2,
    OPCODE_DO = 6,
    OPCODE_FLOAT = 7,
    OPCODE_IDENTIFIER = 8,
    OPCODE_INTEGER = 9,
    OPCODE_LAMDA = 10,
    OPCODE_LIST = 11,
    OPCODE_MAP = 12,
    OPCODE_MODULE = 13,
    OPCODE_NIL = 14,
    OPCODE_PROTOCOL = 15,
    OPCODE_RANGE = 16,
    OPCODE_RESULT = 17,
    OPCODE_SET = 18,
    OPCODE_STRING = 19,
    OPCODE_TOKEN = 20,
    OPCODE_TYPE = 21,
    OPCODE_WHEN = 22
};

typedef enum {
    MODEL_BOOLEAN,
    MODEL_CASE,
    MODEL_DO,
    MODEL_FLOAT,
    MODEL_IDENTIFIER,
    MODEL_INTEGER,
    MODEL_LAMDA,
    MODEL_LIST,
    MODEL_MAP,
    MODEL_MODULE,
    MODEL_NIL,
    MODEL_PROTOCOL,
    MODEL_RANGE,
    MODEL_RESULT,
    MODEL_SET,
    MODEL_STRING,
    MODEL_TOKEN,
    MODEL_TYPE,
    MODEL_WHEN
} Model;

struct Value {
    void *data;
    Model model;
};

Value *VALUE_TRUE = NULL;
Value *VALUE_FALSE = NULL;
Value *VALUE_NIL = NULL;

static Value *ValueCreate(Model model, void *data, Error *error) {
    if (data == NULL)
        return NULL;
    Value *value = MemoryAlloc(sizeof(Value), error);
    if (ERROR(error))
        return NULL; /* missing */
    value->model = model;
    value->data = data;
    return value;
}

Value *ValueDecode(Byte **bytes, Error *error) {
    Integer8 opcode = DecodeInteger8(bytes);
    switch (opcode) {
    case OPCODE_BOOLEAN_TRUE:
        return VALUE_TRUE;
    case OPCODE_BOOLEAN_FALSE:
        return VALUE_FALSE;
    case OPCODE_CASE:
        return ValueCreate(MODEL_CASE, CaseDecode(bytes, error), error);
    case OPCODE_DO:
        return ValueCreate(MODEL_DO, DoDecode(bytes, error), error);
    case OPCODE_FLOAT:
        return ValueCreate(MODEL_FLOAT, FloatDecode(bytes, error), error);
    case OPCODE_IDENTIFIER:
        return ValueCreate(MODEL_IDENTIFIER, IdentifierDecode(bytes, error), error);
    case OPCODE_INTEGER:
        return ValueCreate(MODEL_INTEGER, IntegerDecode(bytes, error), error);
    case OPCODE_LAMDA:
        return ValueCreate(MODEL_LAMDA, LamdaDecode(bytes, error), error);
    case OPCODE_LIST:
        return ValueCreate(MODEL_LIST, ListDecode(bytes, error), error);
    case OPCODE_MAP:
        return ValueCreate(MODEL_MAP, MapDecode(bytes, error), error);
    case OPCODE_MODULE:
        return ValueCreate(MODEL_MODULE, ModuleDecode(bytes, error), error);
    case OPCODE_NIL:
        return VALUE_NIL;
    case OPCODE_PROTOCOL:
        return ValueCreate(MODEL_PROTOCOL, ProtocolDecode(bytes, error), error);
    case OPCODE_RANGE:
        return ValueCreate(MODEL_RANGE, RangeDecode(bytes, error), error);
    case OPCODE_RESULT:
        return ValueCreate(MODEL_RESULT, ResultDecode(bytes, error), error);
    case OPCODE_SET:
        return ValueCreate(MODEL_SET, SetDecode(bytes, error), error);
    case OPCODE_STRING:
        return ValueCreate(MODEL_STRING, StringDecode(bytes, error), error);
    case OPCODE_TOKEN:
        return ValueCreate(MODEL_TOKEN, TokenDecode(bytes, error), error);
    case OPCODE_TYPE:
        return ValueCreate(MODEL_TYPE, TypeDecode(bytes, error), error);
    case OPCODE_WHEN:
        return ValueCreate(MODEL_WHEN, WhenDecode(bytes, error), error);
    }
}

Value *ValueEval(Value *value, Value *context, Error *error) {
    switch (value->model) {
    case MODEL_BOOLEAN:
        return value;
    case MODEL_CASE:
        return CaseEval(value->data, context, error);
    case MODEL_DO:
        return DoEval(value->data, context, error);
    case MODEL_FLOAT:
        return value;
    case MODEL_IDENTIFIER:
        return ValueGetValueForKey(context, value);
    case MODEL_INTEGER:
        return value;
    case MODEL_LAMDA:
        return ValueCreate(MODEL_LAMDA, LamdaEval(value->data, context, error), error);
    case MODEL_LIST:
        return ValueCreate(MODEL_LIST, ListEval(value->data, context, error), error);
    case MODEL_MAP:
        return ValueCreate(MODEL_MAP, MapEval(value->data, context, error), error);
    case MODEL_MODULE:
        return ValueCreate(MODEL_MODULE, ModuleEval(value->data, context, error), error);
    case MODEL_NIL:
        return value;
    case MODEL_PROTOCOL:
        return value;
    case MODEL_RANGE:
        return ValueCreate(MODEL_RANGE, RangeEval(value->data, context, error), error);
    case MODEL_RESULT:
        return ResultEval(value->data, context, error);
    case MODEL_SET:
        return ValueCreate(MODEL_SET, SetEval(value->data, context, error), error);
    case MODEL_STRING:
        return value;
    case MODEL_TOKEN:
        return value;
    case MODEL_TYPE:
        return value;
    case MODEL_WHEN:
        return WhenEval(value->data, context, error);
    }
}

Bool ValueEqual(Value *value, Value *other) {
    if (value->model != other->model)
        return FALSE;
    switch (value->model) {
    case MODEL_BOOLEAN:
        return value == other;
    case MODEL_CASE:
        return CaseEqual(value->data, other->data);
    case MODEL_DO:
        return DoEqual(value->data, other->data);
    case MODEL_FLOAT:
        return FloatEqual(value->data, other->data);
    case MODEL_IDENTIFIER:
        return IdentifierEqual(value->data, other->data);
    case MODEL_INTEGER:
        return IntegerEqual(value->data, other->data);
    case MODEL_LAMDA:
        return LamdaEqual(value->data, other->data);
    case MODEL_LIST:
        return ListEqual(value->data, other->data);
    case MODEL_MAP:
        return MapEqual(value->data, other->data);
    case MODEL_MODULE:
        return ModuleEqual(value->data, other->data);
    case MODEL_NIL:
        return VALUE_TRUE;
    case MODEL_PROTOCOL:
        return ProtocolEqual(value->data, other->data);
    case MODEL_RANGE:
        return RangeEqual(value->data, other->data);
    case MODEL_RESULT:
        return ResultEqual(value->data, other->data);
    case MODEL_SET:
        return SetEqual(value->data, other->data);
    case MODEL_STRING:
        return StringEqual(value->data, other->data);
    case MODEL_TOKEN:
        return TokenEqual(value->data, other->data);
    case MODEL_TYPE:
        return TypeEqual(value->data, other->data);
    case MODEL_WHEN:
        return WhenEqual(value->data, other->data);
    }
}

Value *ValueSetValueForKey(Value *collection, Value *value, Value *key, Error *error) {
    return NULL;
}

Value *ValueGetValueForKey(Value *collection, Value *key) {
    return NULL;
}

Value *ValueCall(Value *value, Value **args, Integer8 count, Error *error) {
    return NULL;
}

Size ValueSize(Value *value) {
    return 0;
}

Size ValueRelease(Value *value) {
    void *data = value->data;
    Model model = value->model;
    MemoryDealloc(value);
    Size size = sizeof(Value);
    switch (model) {
    case MODEL_BOOLEAN:
        return size;
    case MODEL_CASE:
        return size + CaseRelease(data);
    case MODEL_DO:
        return size + DoRelease(data);
    case MODEL_FLOAT:
        return size + FloatRelease(data);
    case MODEL_IDENTIFIER:
        return size + IdentifierRelease(data);
    case MODEL_INTEGER:
        return size + IntegerRelease(data);
    case MODEL_LAMDA:
        return size + LamdaRelease(data);
    case MODEL_LIST:
        return size + ListRelease(data);
    case MODEL_MAP:
        return size + MapRelease(data);
    case MODEL_MODULE:
        return size + ModuleRelease(data);
    case MODEL_NIL:
        return size;
    case MODEL_PROTOCOL:
        return size + ProtocolRelease(data);
    case MODEL_RANGE:
        return size + RangeRelease(data);
    case MODEL_RESULT:
        return size + ResultRelease(data);
    case MODEL_SET:
        return size + SetRelease(data);
    case MODEL_STRING:
        return size + StringRelease(data);
    case MODEL_TOKEN:
        return size + TokenRelease(data);
    case MODEL_TYPE:
        return size + TypeRelease(data);
    case MODEL_WHEN:
        return size + WhenRelease(data);
    }
}
