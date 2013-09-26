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
    PROTOCOL = 12,
    RANGE = 13,
    RESULT = 14,
    SET = 15,
    STRING = 16,
    TOKEN = 17,
    TYPE = 18,
    WHEN = 19
};

struct Value {
    void *data;
    Integer8 model;
};

Size ValueEncode(Value *value, Byte **bytes) {
    switch (value->model) {
    case BINARY:
        return BinaryEncode(value->data, bytes);
    case BOOLEAN:
        return BooleanEncode(value->data, bytes);
    case CASE:
        return CaseEncode(value->data, bytes);
    case DO:
        return DoEncode(value->data, bytes);
    case FLOAT:
        return FloatEncode(value->data, bytes);
    case IDENTIFIER:
        return IdentifierEncode(value->data, bytes);
    case INTEGER:
        return IntegerEncode(value->data, bytes);
    case LAMDA:
        return LamdaEncode(value->data, bytes);
    case LIST:
        return ListEncode(value->data, bytes);
    case MAP:
        return MapEncode(value->data, bytes);
    case MODULE:
        return ModuleEncode(value->data, bytes);
    case NIL:
        return NilEncode(value->data, bytes);
    case PROTOCOL:
        return ProtocolEncode(value->data, bytes);
    case RANGE:
        return RangeEncode(value->data, bytes);
    case RESULT:
        return ResultEncode(value->data, bytes);
    case SET:
        return SetEncode(value->data, bytes);
    case STRING:
        return StringEncode(value->data, bytes);
    case TOKEN:
        return TokenEncode(value->data, bytes);
    case TYPE:
        return TypeEncode(value->data, bytes);
    case WHEN:
        return WhenEncode(value->data, bytes);
    }
}

Value *ValueDecode(Byte **bytes, Error *error) {
    return NULL;
}

Value *ValueEval(Value *value, Value *context, Error *error) {
    return NULL;
}

Bool ValueEqual(Value *value, Value *other) {
    if (value->model != other->model)
        return FALSE;
    switch (value->model) {
    case BINARY:
        return BinaryEqual(value->data, other->data);
    case BOOLEAN:
        return BooleanEqual(value->data, other->data);
    case CASE:
        return CaseEqual(value->data, other->data);
    case DO:
        return DoEqual(value->data, other->data);
    case FLOAT:
        return FloatEqual(value->data, other->data);
    case IDENTIFIER:
        return IdentifierEqual(value->data, other->data);
    case INTEGER:
        return IntegerEqual(value->data, other->data);
    case LAMDA:
        return LamdaEqual(value->data, other->data);
    case LIST:
        return ListEqual(value->data, other->data);
    case MAP:
        return MapEqual(value->data, other->data);
    case MODULE:
        return ModuleEqual(value->data, other->data);
    case NIL:
        return NilEqual(value->data, other->data);
    case PROTOCOL:
        return ProtocolEqual(value->data, other->data);
    case RANGE:
        return RangeEqual(value->data, other->data);
    case RESULT:
        return ResultEqual(value->data, other->data);
    case SET:
        return SetEqual(value->data, other->data);
    case STRING:
        return StringEqual(value->data, other->data);
    case TOKEN:
        return TokenEqual(value->data, other->data);
    case TYPE:
        return TypeEqual(value->data, other->data);
    case WHEN:
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
    switch (value->model) {
    case BINARY:
        return INTEGER_8_SIZE + BinarySize(value->data);
    case BOOLEAN:
        return INTEGER_8_SIZE + BooleanSize(value->data);
    case CASE:
        return INTEGER_8_SIZE + CaseSize(value->data);
    case DO:
        return INTEGER_8_SIZE + DoSize(value->data);
    case FLOAT:
        return INTEGER_8_SIZE + FloatSize(value->data);
    case IDENTIFIER:
        return INTEGER_8_SIZE + IdentifierSize(value->data);
    case INTEGER:
        return INTEGER_8_SIZE + IntegerSize(value->data);
    case LAMDA:
        return INTEGER_8_SIZE + LamdaSize(value->data);
    case LIST:
        return INTEGER_8_SIZE + ListSize(value->data);
    case MAP:
        return INTEGER_8_SIZE + MapSize(value->data);
    case MODULE:
        return INTEGER_8_SIZE + ModuleSize(value->data);
    case NIL:
        return INTEGER_8_SIZE + NilSize(value->data);
    case PROTOCOL:
        return INTEGER_8_SIZE + ProtocolSize(value->data);
    case RANGE:
        return INTEGER_8_SIZE + RangeSize(value->data);
    case RESULT:
        return INTEGER_8_SIZE + ResultSize(value->data);
    case SET:
        return INTEGER_8_SIZE + SetSize(value->data);
    case STRING:
        return INTEGER_8_SIZE + StringSize(value->data);
    case TOKEN:
        return INTEGER_8_SIZE + TokenSize(value->data);
    case TYPE:
        return INTEGER_8_SIZE + TypeSize(value->data);
    case WHEN:
        return INTEGER_8_SIZE + WhenSize(value->data);
    }
}

Size ValueRelease(Value *value) {
    void *data = value->data;
    Integer8 model = value->model;
    MemoryDealloc(value);
    switch (model) {
    case BOOLEAN:
        return sizeof(Value) + BooleanRelease(data);
    case CASE:
        return sizeof(Value) + CaseRelease(data);
    case DO:
        return sizeof(Value) + DoRelease(data);
    case FLOAT:
        return sizeof(Value) + FloatRelease(data);
    case IDENTIFIER:
        return sizeof(Value) + IdentifierRelease(data);
    case INTEGER:
        return sizeof(Value) + IntegerRelease(data);
    case LAMDA:
        return sizeof(Value) + LamdaRelease(data);
    case LIST:
        return sizeof(Value) + ListRelease(data);
    case MAP:
        return sizeof(Value) + MapRelease(data);
    case MODULE:
        return sizeof(Value) + ModuleRelease(data);
    case NIL:
        return sizeof(Value) + NilRelease(data);
    case PROTOCOL:
        return sizeof(Value) + ProtocolRelease(data);
    case RANGE:
        return sizeof(Value) + RangeRelease(data);
    case RESULT:
        return sizeof(Value) + ResultRelease(data);
    case SET:
        return sizeof(Value) + SetRelease(data);
    case STRING:
        return sizeof(Value) + StringRelease(data);
    case TOKEN:
        return sizeof(Value) + TokenRelease(data);
    case TYPE:
        return sizeof(Value) + TypeRelease(data);
    case WHEN:
        return sizeof(Value) + WhenRelease(data);
    }
}
