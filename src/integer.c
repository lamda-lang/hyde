#include "integer.h"

struct Integer {
    Value base;
    Integer64 value;
};

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

Value *IntegerDecode(Byte **bytes, Error *error) {
    Integer64 value = DecodeInteger64FLE(bytes);
    Integer *integer = Create(value, error);
    return BridgeFromInteger(integer);
}

void IntegerDealloc(Value *integerValue) {
    MemoryDealloc(integerValue);
}

Integer64 IntegerHash(Value *integerValue) {
    return BridgeToInteger(integerValue)->value;
}

Value *IntegerSum(Value *integerValue, Value *otherValue, Error *error) {
  Integer64 sum = BridgeToInteger(integerValue)->value + BridgeToInteger(otherValue)->value;
  Integer *integer = Create(sum, error);
  return BridgeFromInteger(integer);
}

Value *IntegerEval(Value *integerValue, bool pure, Error *error) {
    return integerValue;
}
