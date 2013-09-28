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

static Value *ValueCreate(Integer8 model, void *data, Error *error) {
    Value *value = MemoryAlloc(sizeof(Value), error);
    if (ERROR(error))
        return NULL;
    value->model = model;
    value->data = data;
    return value;
}

static Size ValueEncodeModel(Integer8 model, void *data, Byte **bytes) {
    switch (model) {
    case BINARY:
        return BinaryEncode(data, bytes);
    case BOOLEAN:
        return BooleanEncode(data, bytes);
    case CASE:
        return CaseEncode(data, bytes);
    case DO:
        return DoEncode(data, bytes);
    case FLOAT:
        return FloatEncode(data, bytes);
    case IDENTIFIER:
        return IdentifierEncode(data, bytes);
    case INTEGER:
        return IntegerEncode(data, bytes);
    case LAMDA:
        return LamdaEncode(data, bytes);
    case LIST:
        return ListEncode(data, bytes);
    case MAP:
        return MapEncode(data, bytes);
    case MODULE:
        return ModuleEncode(data, bytes);
    case NIL:
        return NilEncode(data, bytes);
    case PROTOCOL:
        return ProtocolEncode(data, bytes);
    case RANGE:
        return RangeEncode(data, bytes);
    case RESULT:
        return ResultEncode(data, bytes);
    case SET:
        return SetEncode(data, bytes);
    case STRING:
        return StringEncode(data, bytes);
    case TOKEN:
        return TokenEncode(data, bytes);
    case TYPE:
        return TypeEncode(data, bytes);
    case WHEN:
        return WhenEncode(data, bytes);
    }
}

static void *ValueDecodeModel(Integer8 model, Byte **bytes, Error *error) {
    switch (model) {
    case BINARY:
        return BinaryDecode(bytes, error);
    case BOOLEAN:
        return BooleanDecode(bytes, error);
    case CASE:
        return CaseDecode(bytes, error);
    case DO:
        return DoDecode(bytes, error);
    case FLOAT:
        return FloatDecode(bytes, error);
    case IDENTIFIER:
        return IdentifierDecode(bytes, error);
    case INTEGER:
        return IntegerDecode(bytes, error);
    case LAMDA:
        return LamdaDecode(bytes, error);
    case LIST:
        return ListDecode(bytes, error);
    case MAP:
        return MapDecode(bytes, error);
    case MODULE:
        return ModuleDecode(bytes, error);
    case NIL:
        return NilDecode(bytes, error);
    case PROTOCOL:
        return ProtocolDecode(bytes, error);
    case RANGE:
        return RangeDecode(bytes, error);
    case RESULT:
        return ResultDecode(bytes, error);
    case SET:
        return SetDecode(bytes, error);
    case STRING:
        return StringDecode(bytes, error);
    case TOKEN:
        return TokenDecode(bytes, error);
    case TYPE:
        return TypeDecode(bytes, error);
    case WHEN:
        return WhenDecode(bytes, error);
    }
}

static Bool ValueEqualModel(Integer8 model, void *data, void *other) {
    switch (model) {
    case BINARY:
        return BinaryEqual(data, other);
    case BOOLEAN:
        return BooleanEqual(data, other);
    case CASE:
        return CaseEqual(data, other);
    case DO:
        return DoEqual(data, other);
    case FLOAT:
        return FloatEqual(data, other);
    case IDENTIFIER:
        return IdentifierEqual(data, other);
    case INTEGER:
        return IntegerEqual(data, other);
    case LAMDA:
        return LamdaEqual(data, other);
    case LIST:
        return ListEqual(data, other);
    case MAP:
        return MapEqual(data, other);
    case MODULE:
        return ModuleEqual(data, other);
    case NIL:
        return NilEqual(data, other);
    case PROTOCOL:
        return ProtocolEqual(data, other);
    case RANGE:
        return RangeEqual(data, other);
    case RESULT:
        return ResultEqual(data, other);
    case SET:
        return SetEqual(data, other);
    case STRING:
        return StringEqual(data, other);
    case TOKEN:
        return TokenEqual(data, other);
    case TYPE:
        return TypeEqual(data, other);
    case WHEN:
        return WhenEqual(data, other);
    }
} 

static Size ValueSizeModel(Integer8 model, void *data) {
    switch (model) {
    case BINARY:
        return BinarySize(data);
    case BOOLEAN:
        return BooleanSize(data);
    case CASE:
        return CaseSize(data);
    case DO:
        return DoSize(data);
    case FLOAT:
        return FloatSize(data);
    case IDENTIFIER:
        return IdentifierSize(data);
    case INTEGER:
        return IntegerSize(data);
    case LAMDA:
        return LamdaSize(data);
    case LIST:
        return ListSize(data);
    case MAP:
        return MapSize(data);
    case MODULE:
        return ModuleSize(data);
    case NIL:
        return NilSize(data);
    case PROTOCOL:
        return ProtocolSize(data);
    case RANGE:
        return RangeSize(data);
    case RESULT:
        return ResultSize(data);
    case SET:
        return SetSize(data);
    case STRING:
        return StringSize(data);
    case TOKEN:
        return TokenSize(data);
    case TYPE:
        return TypeSize(data);
    case WHEN:
        return WhenSize(data);
    }
}

static Size ValueReleaseModel(Integer8 model, void *data) {
    switch (model) {
    case BOOLEAN:
        return BooleanRelease(data);
    case CASE:
        return CaseRelease(data);
    case DO:
        return DoRelease(data);
    case FLOAT:
        return FloatRelease(data);
    case IDENTIFIER:
        return IdentifierRelease(data);
    case INTEGER:
        return IntegerRelease(data);
    case LAMDA:
        return LamdaRelease(data);
    case LIST:
        return ListRelease(data);
    case MAP:
        return MapRelease(data);
    case MODULE:
        return ModuleRelease(data);
    case NIL:
        return NilRelease(data);
    case PROTOCOL:
        return ProtocolRelease(data);
    case RANGE:
        return RangeRelease(data);
    case RESULT:
        return ResultRelease(data);
    case SET:
        return SetRelease(data);
    case STRING:
        return StringRelease(data);
    case TOKEN:
        return TokenRelease(data);
    case TYPE:
        return TypeRelease(data);
    case WHEN:
        return WhenRelease(data);
    }
}

static Value *ValueCallModel(Integer8 model, void *data, Value **args, Integer8 count, Error *error) {
    switch(model) {
    case LAMDA:
        return LamdaCall(data, args, count, error);
    default:
        goto error;
    }

error:
    *error = ERROR_INVALID_TARGET;
    return NULL;
}

static Value *ValueEvalModel(Value *value, Integer8 model, void *data, Value *context, Error *error) {
    switch (model) {
    case BOOLEAN:
        return BooleanEval(value, data, context, error);
    case CASE:
        return CaseEval(value, data, context, error);
    case DO:
        return DoEval(value, data, context, error);
    case FLOAT:
        return FloatEval(value, data, context, error);
    case IDENTIFIER:
        return IdentifierEval(value, data, context, error);
    case INTEGER:
        return IntegerEval(value, data, context, error);
    case LAMDA:
        return LamdaEval(value, data, context, error);
    case LIST:
        return ListEval(value, data, context, error);
    case MAP:
        return MapEval(value, data, context, error);
    case MODULE:
        return ModuleEval(value, data, context, error);
    case NIL:
        return NilEval(value, data, context, error);
    case PROTOCOL:
        return ProtocolEval(value, data, context, error);
    case RANGE:
        return RangeEval(value, data, context, error);
    case RESULT:
        return ResultEval(value, data, context, error);
    case SET:
        return SetEval(value, data, context, error);
    case STRING:
        return StringEval(value, data, context, error);
    case TOKEN:
        return TokenEval(value, data, context, error);
    case TYPE:
        return TypeEval(value, data, context, error);
    case WHEN:
        return WhenEval(value, data, context, error);
    }
}

Value *ValueCopy(void *data, Error *error) {
}

Size ValueEncode(Value *value, Byte **bytes) {
    EncodeInteger8(value->model, bytes);
    ValueEncodeModel(value->model, value->data, bytes);
    return ValueSize(value);
}

Value *ValueDecode(Byte **bytes, Error *error) {
    Integer8 model = DecodeInteger8(bytes);
    void *data = ValueDecodeModel(model, bytes, error);
    if (ERROR(error))
        return NULL;
    Value *value = ValueCreate(model, data, error);
    if (ERROR(error))
        goto data;
    return value;

data:
    ValueReleaseModel(model, data);
    return NULL;
}

Bool ValueEqual(Value *value, Value *other) {
    if (value == other)
        return TRUE;
    if (value->model != other->model)
        return FALSE;
    return ValueEqualModel(value->model, value->data, other->data);
}

Size ValueSize(Value *value) {
    return INTEGER_8_SIZE + ValueSizeModel(value->model, value->data);
}

Size ValueRelease(Value *value) {
    Size size = sizeof(Value) + ValueReleaseModel(value->model, value->data);
    MemoryDealloc(value);
    return size;
}

Value *ValueCall(Value *value, Value **args, Integer8 count, Error *error) {
    return ValueCallModel(value->model, value->data, args, count, error);
}

Value *ValueEval(Value *value, Value *context, Error *error) {
    return ValueEvalModel(value, value->model, value->data, context, error);
}

Value *ValueSetValueForKey(Value *collection, Value *value, Value *key, Error *error) {
    return NULL;
}

Value *ValueGetValueForKey(Value *collection, Value *key) {
    return NULL;
}
