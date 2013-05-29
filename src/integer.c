#include "integer.h"

struct Integer {
    Value base;
    Integer64 value;
};

Integer *IntegerCreate(Integer64 value, Error *error) {
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

Value *IntegerValueBridge(Integer *integer) {
    return (Value *)integer;
}

void IntegerDealloc(Value *integerValue) {
    MemoryDealloc(integerValue);
}

Integer64 IntegerHash(Value *integerValue) {
    Integer *integer = ValueIntegerBridge(integerValue);
    return integer->value;
}

Integer *IntegerSum(Integer *integer, Integer *other, Error *error) {
  Integer64 sum = integer->value + other->value;
  return IntegerCreate(sum, error);
}
