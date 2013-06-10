#include "integer.h"

struct Integer {
    Value base;
    Integer64 value;
};

static Integer *Create(Integer64 value, Error *error) {
    Size size = sizeof(Integer);
    Integer *integer = MemoryAlloc(size, error);
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
    return IntegerValueBridge(integer);
}

Value *IntegerValueBridge(Integer *integer) {
    return (Value *)integer;
}

void IntegerDealloc(Value *integerValue) {
    MemoryDealloc(integerValue);
}

Integer64 IntegerHash(Value *integerValue) {
    return ValueIntegerBridge(integerValue)->value;
}

Integer *IntegerSum(Integer *integer, Integer *other, Error *error) {
  Integer64 sum = integer->value + other->value;
  return Create(sum, error);
}

Value *IntegerEval(Value *integerValue, Error *error) {
    return integerValue;
}
