#include "integer.h"

struct Integer {
    Type *type;
    Integer64 value;
};

typedef struct {
    Integer64 value;
} Model;

static Integer *Create(Integer64 value, Value **error) {
    Integer *integer = MemoryAlloc(sizeof(Integer), error);
    if (integer == NULL) {
        goto returnValue;
    }
    integer->type = TypeInteger;
    integer->value = value;
    return integer;

returnValue:
    return NULL;
}

void *IntegerDecode(Byte **bytes, Value **error) {
    Model *model = MemoryAlloc(sizeof(Model), error);
    if (model == NULL) {
        goto returnValue;
    }
    model->value = DecodeInteger64FLE(bytes);
    return model;

returnValue:
    return NULL;
}

void IntegerDealloc(Value *integerValue) {
    MemoryDealloc(integerValue);
}

Integer64 IntegerHash(Value *integerValue) {
    return BridgeToInteger(integerValue)->value;
}

Bool IntegerEqual(Value *integerValue, Value *otherValue) {
    return BridgeToInteger(integerValue)->value == BridgeToInteger(otherValue)->value;
}

Value *IntegerSum(Value **args, Integer8 count, Value **error) {
    Integer *integer = BridgeToInteger(args[0]);
    Integer *other = BridgeToInteger(args[1]);
    Integer *result = Create(integer->value + other->value, error);
    return BridgeFromInteger(result);
}
