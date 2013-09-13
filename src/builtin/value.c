#include <builtin/value.h>

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

Bool ValueEqual(Value *value, Value *other) {
    if (value->model != other->model)
        return FALSE;
    switch (value->model) {
    case MODEL_BOOLEAN:
        return BooleanEqual(value->data, other->data);
    case MODEL_CASE:
        return CaseEqual(value->data, other->data);
    case MODEL_COMPREHENSION_LIST:
        return ComprehensionEqual(value->data, other->data);
    case MODEL_COMPREHENSION_MAP:
        return ComprehensionEqual(value->data, other->data);
    case MODEL_COMPREHENSION_SET:
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
    case MODEL_COMPREHENSION_LIST:
        return size + ComprehensionRelease(data);
    case MODEL_COMPREHENSION_MAP:
        return size + ComprehensionRelease(data);
    case MODEL_COMPREHENSION_SET:
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
