#include "integer.h"

struct Integer {
    Value base;
    Integer64 value;
};

typedef struct {
    Integer64 value;
} Model;

static Integer *Create(Integer64 value, Error *error) {
    Integer *integer = MemoryAlloc(sizeof(Integer), error);
    if (integer == NULL) {
        goto returnError;
    }
    integer->base = TypeInteger;
    integer->value = value;
    return integer;

returnError:
    return NULL;
}

void *IntegerDecode(Byte **bytes, Error *error) {
    Model *model = MemoryAlloc(sizeof(Model), error);
    if (model == NULL) {
	goto returnError;
    }
    model->value = DecodeInteger64FLE(bytes);
    return model;

returnError:
    return NULL;
}

Value *IntegerEval(void *data, Code *code, bool pure, Error *error) {
    Model *model = data;
    Integer *integer = Create(model->value, error);
    return BridgeFromInteger(integer);
}

void IntegerDealloc(Value *integerValue) {
    MemoryDealloc(integerValue);
}

Integer64 IntegerHash(Value *integerValue) {
    return BridgeToInteger(integerValue)->value;
}

bool IntegerEqual(Value *integerValue, Value *otherValue) {
    return BridgeToInteger(integerValue)->value == BridgeToInteger(otherValue)->value;
}

Value *IntegerSum(Value *integerValue, Value *otherValue, Error *error) {
  Integer64 sum = BridgeToInteger(integerValue)->value + BridgeToInteger(otherValue)->value;
  Integer *integer = Create(sum, error);
  return BridgeFromInteger(integer);
}
