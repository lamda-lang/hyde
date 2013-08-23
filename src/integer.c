#include "integer.h"

struct Integer {
    Type *type;
    Integer64 value;
};

typedef struct {
    Integer64 value;
} Model;

static Integer *Create(Integer64 value, VALUE **error) {
    Integer *integer = MemoryAlloc(sizeof(Integer), error);
    if (integer == NULL) {
        goto returnVALUE;
    }
    integer->type = TypeInteger;
    integer->value = value;
    return integer;

returnVALUE:
    return NULL;
}

void *IntegerDecode(Byte **bytes, VALUE **error) {
    Model *model = MemoryAlloc(sizeof(Model), error);
    if (model == NULL) {
        goto returnVALUE;
    }
    model->value = DecodeInteger64FLE(bytes);
    return model;

returnVALUE:
    return NULL;
}

void IntegerDealloc(VALUE *integerVALUE) {
    MemoryDealloc(integerVALUE);
}

Integer64 IntegerHash(VALUE *integerVALUE) {
    return BridgeToInteger(integerVALUE)->value;
}

Bool IntegerEqual(VALUE *integerVALUE, VALUE *otherVALUE) {
    return BridgeToInteger(integerVALUE)->value == BridgeToInteger(otherVALUE)->value;
}

VALUE *IntegerSum(VALUE **args, Integer8 count, VALUE **error) {
    Integer *integer = BridgeToInteger(args[0]);
    Integer *other = BridgeToInteger(args[1]);
    Integer *result = Create(integer->value + other->value, error);
    return BridgeFromInteger(result);
}
