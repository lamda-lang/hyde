#include "value.h"

typedef enum {
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
} Model;

struct Value {
    void *data;
    Integer8 model;
};

static Size ValueReleaseModel(Model model, void *data) {
    switch (model) {
    case MODEL_BINARY:
        return BinaryRelease(data);
    case MODEL_BOOLEAN:
        return BooleanRelease(data);
    case MODEL_CASE:
        return CaseRelease(data);
    case MODEL_DO:
        return DoRelease(data);
    case MODEL_FLOAT:
        return FloatRelease(data);
    case MODEL_IDENTIFIER:
        return IdentifierRelease(data);
    case MODEL_INTEGER:
        return IntegerRelease(data);
    case MODEL_LAMDA:
        return LamdaRelease(data);
    case MODEL_LIST:
        return ListRelease(data);
    case MODEL_MAP:
        return MapRelease(data);
    case MODEL_MODULE:
        return ModuleRelease(data);
    case MODEL_NIL:
        return NilRelease(data);
    case MODEL_RANGE:
        return RangeRelease(data);
    case MODEL_RESULT:
        return ResultRelease(data);
    case MODEL_SET:
        return SetRelease(data);
    case MODEL_STRING:
        return StringRelease(data);
    case MODEL_TOKEN:
        return TokenRelease(data);
    case MODEL_TYPE:
        return TypeRelease(data);
    case MODEL_WHEN:
        return WhenRelease(data);
    }
}

static Value *ValueCreate(Integer8 model, void *data, Error *error) {
    Value *value = MemoryAlloc(sizeof(Value), error);
    if (ERROR(error))
        goto data;
    value->model = model;
    value->data = data;
    return value;

data:
    ValueReleaseModel(model, data);
    return NULL;
}  

static Size ValueEncodeModel(Model model, void *data, Byte **bytes) {
    switch (model) {
    case MODEL_BINARY:
        return BinaryEncode(data, bytes);
    case MODEL_BOOLEAN:
        return BooleanEncode(data, bytes);
    case MODEL_CASE:
        return CaseEncode(data, bytes);
    case MODEL_DO:
        return DoEncode(data, bytes);
    case MODEL_FLOAT:
        return FloatEncode(data, bytes);
    case MODEL_IDENTIFIER:
        return IdentifierEncode(data, bytes);
    case MODEL_INTEGER:
        return IntegerEncode(data, bytes);
    case MODEL_LAMDA:
        return LamdaEncode(data, bytes);
    case MODEL_LIST:
        return ListEncode(data, bytes);
    case MODEL_MAP:
        return MapEncode(data, bytes);
    case MODEL_MODULE:
        return ModuleEncode(data, bytes);
    case MODEL_NIL:
        return NilEncode(data, bytes);
    case MODEL_RANGE:
        return RangeEncode(data, bytes);
    case MODEL_RESULT:
        return ResultEncode(data, bytes);
    case MODEL_SET:
        return SetEncode(data, bytes);
    case MODEL_STRING:
        return StringEncode(data, bytes);
    case MODEL_TOKEN:
        return TokenEncode(data, bytes);
    case MODEL_TYPE:
        return TypeEncode(data, bytes);
    case MODEL_WHEN:
        return WhenEncode(data, bytes);
    }
}

static void *ValueDecodeModel(Model model, Byte **bytes, Error *error) {
    switch (model) {
    case MODEL_BINARY:
        return BinaryDecode(bytes, error);
    case MODEL_BOOLEAN:
        return BooleanDecode(bytes, error);
    case MODEL_CASE:
        return CaseDecode(bytes, error);
    case MODEL_DO:
        return DoDecode(bytes, error);
    case MODEL_FLOAT:
        return FloatDecode(bytes, error);
    case MODEL_IDENTIFIER:
        return IdentifierDecode(bytes, error);
    case MODEL_INTEGER:
        return IntegerDecode(bytes, error);
    case MODEL_LAMDA:
        return LamdaDecode(bytes, error);
    case MODEL_LIST:
        return ListDecode(bytes, error);
    case MODEL_MAP:
        return MapDecode(bytes, error);
    case MODEL_MODULE:
        return ModuleDecode(bytes, error);
    case MODEL_NIL:
        return NilDecode(bytes, error);
    case MODEL_RANGE:
        return RangeDecode(bytes, error);
    case MODEL_RESULT:
        return ResultDecode(bytes, error);
    case MODEL_SET:
        return SetDecode(bytes, error);
    case MODEL_STRING:
        return StringDecode(bytes, error);
    case MODEL_TOKEN:
        return TokenDecode(bytes, error);
    case MODEL_TYPE:
        return TypeDecode(bytes, error);
    case MODEL_WHEN:
        return WhenDecode(bytes, error);
    }
}

static Bool ValueEqualModel(Model model, void *data, void *other) {
    switch (model) {
    case MODEL_BINARY:
        return BinaryEqual(data, other);
    case MODEL_BOOLEAN:
        return BooleanEqual(data, other);
    case MODEL_CASE:
        return CaseEqual(data, other);
    case MODEL_DO:
        return DoEqual(data, other);
    case MODEL_FLOAT:
        return FloatEqual(data, other);
    case MODEL_IDENTIFIER:
        return IdentifierEqual(data, other);
    case MODEL_INTEGER:
        return IntegerEqual(data, other);
    case MODEL_LAMDA:
        return LamdaEqual(data, other);
    case MODEL_LIST:
        return ListEqual(data, other);
    case MODEL_MAP:
        return MapEqual(data, other);
    case MODEL_MODULE:
        return ModuleEqual(data, other);
    case MODEL_NIL:
        return NilEqual(data, other);
    case MODEL_RANGE:
        return RangeEqual(data, other);
    case MODEL_RESULT:
        return ResultEqual(data, other);
    case MODEL_SET:
        return SetEqual(data, other);
    case MODEL_STRING:
        return StringEqual(data, other);
    case MODEL_TOKEN:
        return TokenEqual(data, other);
    case MODEL_TYPE:
        return TypeEqual(data, other);
    case MODEL_WHEN:
        return WhenEqual(data, other);
    }
} 

static Size ValueSizeModel(Model model, void *data) {
    switch (model) {
    case MODEL_BINARY:
        return BinarySize(data);
    case MODEL_BOOLEAN:
        return BooleanSize(data);
    case MODEL_CASE:
        return CaseSize(data);
    case MODEL_DO:
        return DoSize(data);
    case MODEL_FLOAT:
        return FloatSize(data);
    case MODEL_IDENTIFIER:
        return IdentifierSize(data);
    case MODEL_INTEGER:
        return IntegerSize(data);
    case MODEL_LAMDA:
        return LamdaSize(data);
    case MODEL_LIST:
        return ListSize(data);
    case MODEL_MAP:
        return MapSize(data);
    case MODEL_MODULE:
        return ModuleSize(data);
    case MODEL_NIL:
        return NilSize(data);
    case MODEL_RANGE:
        return RangeSize(data);
    case MODEL_RESULT:
        return ResultSize(data);
    case MODEL_SET:
        return SetSize(data);
    case MODEL_STRING:
        return StringSize(data);
    case MODEL_TOKEN:
        return TokenSize(data);
    case MODEL_TYPE:
        return TypeSize(data);
    case MODEL_WHEN:
        return WhenSize(data);
    }
}

static Value *ValueCallModel(Integer8 model, void *data, Value **args, Integer8 count, Error *error) {
    switch(model) {
    case MODEL_LAMDA:
        return LamdaCall(data, args, count, error);
    default:
        goto error;
    }

error:
    *error = ERROR_INVALID_TARGET;
    return NULL;
}

static Value *ValueEvalModel(Value *value, Model model, void *data, Value *context, Error *error) {
    switch (model) {
    case MODEL_BINARY:
        return BinaryEval(value, data, context, error);
    case MODEL_BOOLEAN:
        return BooleanEval(value, data, context, error);
    case MODEL_CASE:
        return CaseEval(value, data, context, error);
    case MODEL_DO:
        return DoEval(value, data, context, error);
    case MODEL_FLOAT:
        return FloatEval(value, data, context, error);
    case MODEL_IDENTIFIER:
        return IdentifierEval(value, data, context, error);
    case MODEL_INTEGER:
        return IntegerEval(value, data, context, error);
    case MODEL_LAMDA:
        return LamdaEval(value, data, context, error);
    case MODEL_LIST:
        return ListEval(value, data, context, error);
    case MODEL_MAP:
        return MapEval(value, data, context, error);
    case MODEL_MODULE:
        return ModuleEval(value, data, context, error);
    case MODEL_NIL:
        return NilEval(value, data, context, error);
    case MODEL_RANGE:
        return RangeEval(value, data, context, error);
    case MODEL_RESULT:
        return ResultEval(value, data, context, error);
    case MODEL_SET:
        return SetEval(value, data, context, error);
    case MODEL_STRING:
        return StringEval(value, data, context, error);
    case MODEL_TOKEN:
        return TokenEval(value, data, context, error);
    case MODEL_TYPE:
        return TypeEval(value, data, context, error);
    case MODEL_WHEN:
        return WhenEval(value, data, context, error);
    }
}

Value *ValueList(List *list, Error *error) {
    return ValueCreate(MODEL_LIST, list, error);
}

Value *ValueMap(Map *map, Error *error) {
    return ValueCreate(MODEL_MAP, map, error);
}

Value *ValueModule(Module *module, Error *error) {
    return ValueCreate(MODEL_MODULE, module, error);
}

Value *ValueLamda(Lamda *lamda, Error *error) {
    return ValueCreate(MODEL_LAMDA, lamda, error);
}

Value *ValueSet(Set *set, Error *error) {
    return ValueCreate(MODEL_SET, set, error);
}

Value *ValueRange(Range *range, Error *error) {
    return ValueCreate(MODEL_RANGE, range, error);
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
    return ValueCreate(model, data, error);
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
