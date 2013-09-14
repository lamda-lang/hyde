#include <builtin/value.h>

#define OPCODE_BOOLEAN_TRUE 0
#define OPCODE_BOOLEAN_FALSE 1
#define OPCODE_CASE 2
#define OPCODE_COMPREHENSION_LIST 3
#define OPCODE_COMPREHENSION_MAP 4
#define OPCODE_COMPREHENSION_SET 5
#define OPCODE_DO 6
#define OPCODE_FLOAT 7
#define OPCODE_IDENTIFIER 8
#define OPCODE_INTEGER 9
#define OPCODE_LAMDA 10
#define OPCODE_LIST 11
#define OPCODE_MAP 12
#define OPCODE_MODULE 13
#define OPCODE_NIL 14
#define OPCODE_PROTOCOL 15
#define OPCODE_RANGE 16
#define OPCODE_RESULT 17
#define OPCODE_SET 18
#define OPCODE_STRING 19
#define OPCODE_TOKEN 20
#define OPCODE_TYPE 21
#define OPCODE_WHEN 22

struct Value {
    void *data;
    Model model;
};

Value *ValueCreate(Model model, void *data) {
    Value *value = MemoryAlloc(sizeof(Value));
    if (value == NULL)
        return NULL;
    value->model = model;
    value->data = data;
    return value;
}

Value *ValueEval(Value *value, Value *context) {
    switch (value->model) {
    case MODEL_BOOLEAN:
        return value;
    case MODEL_CASE:
        return CaseEval(value->data, context);
    case MODEL_COMPREHENSION:
        return ComprehensionEval(value->data, context);
    case MODEL_DO:
        return DoEval(value->data, context);
    case MODEL_FLOAT:
        return value;
    case MODEL_IDENTIFIER:
        return IdentifierEval(value->data, context);
    case MODEL_INTEGER:
        return value;
    case MODEL_LAMDA:
        return LamdaEval(value->data, context);
    case MODEL_LIST:
        return ListEval(value->data, context);
    case MODEL_MAP:
        return MapEval(value->data, context);
    case MODEL_MODULE:
        return ModuleEval(value->data, context);
    case MODEL_NIL:
        return value;
    case MODEL_PROTOCOL:
        return value;
    case MODEL_RANGE:
        return RangeEval(value->data, context);
    case MODEL_RESULT:
        return ResultEval(value->data, context);
    case MODEL_SET:
        return SetEval(value->data, context);
    case MODEL_STRING:
        return value;
    case MODEL_TOKEN:
        return value;
    case MODEL_TYPE:
        return value;
    case MODEL_WHEN:
        return WhenEval(value->data, context);
    }
}

Value *ValueDecode(Byte **bytes) {
    Integer8 opcode = DecodeInteger8(bytes);
    switch (opcode) {
    case OPCODE_BOOLEAN_TRUE:
        return BooleanCreate(TRUE);
    case OPCODE_BOOLEAN_FALSE:
        return BooleanCreate(FALSE);
    case OPCODE_CASE:
        return CaseDecode(bytes);
    case OPCODE_COMPREHENSION_LIST:
        return ComprehensionDecode(bytes);
    case OPCODE_COMPREHENSION_MAP:
        return ComprehensionDecode(bytes);
    case OPCODE_COMPREHENSION_SET:
        return ComprehensionDecode(bytes);
    case OPCODE_DO:
        return DoDecode(bytes);
    case OPCODE_FLOAT:
        return FloatDecode(bytes);
    case OPCODE_IDENTIFIER:
        return IdentifierDecode(bytes);
    case OPCODE_INTEGER:
        return IntegerDecode(bytes);
    case OPCODE_LAMDA:
        return LamdaDecode(bytes);
    case OPCODE_LIST:
        return ListDecode(bytes);
    case OPCODE_MAP:
        return MapDecode(bytes);
    case OPCODE_MODULE:
        return ModuleDecode(bytes);
    case OPCODE_NIL:
        return ValueCreate(MODEL_NIL, NULL);
    case OPCODE_PROTOCOL:
        return ProtocolDecode(bytes);
    case OPCODE_RANGE:
        return RangeDecode(bytes);
    case OPCODE_RESULT:
        return ResultDecode(bytes);
    case OPCODE_SET:
        return SetDecode(bytes);
    case OPCODE_STRING:
        return StringDecode(bytes);
    case OPCODE_TOKEN:
        return TokenDecode(bytes);
    case OPCODE_TYPE:
        return TypeDecode(bytes);
    case OPCODE_WHEN:
        return WhenDecode(bytes);
    }
}

Bool ValueEqual(Value *value, Value *other) {
    if (value->model != other->model)
        return FALSE;
    switch (value->model) {
    case MODEL_BOOLEAN:
        return BooleanEqual(value->data, other->data);
    case MODEL_CASE:
        return CaseEqual(value->data, other->data);
    case MODEL_COMPREHENSION:
        return ComprehensionEqual(value->data, other->data);
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
        return TRUE;
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

Size ValueRelease(Value *value) {
    void *data = value->data;
    Model model = value->model;
    MemoryDealloc(value);
    Size size = sizeof(Value);
    switch (model) {
    case MODEL_BOOLEAN:
        return size + BooleanRelease(data);
    case MODEL_CASE:
        return size + CaseRelease(data);
    case MODEL_COMPREHENSION:
        return size + ComprehensionRelease(data);
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
