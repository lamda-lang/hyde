#include "integer.h"

struct Integer {
    Value base;
    Integer64 value;
};

Integer *IntegerCreate(Integer64 value, Exception *exception) {
    Integer *integer = MemoryAlloc(sizeof(Integer), exception);
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

Integer *IntegerSum(Integer *integer, Integer *other, Exception *exception) {
  Integer64 sum = integer->value + other->value;
  return IntegerCreate(sum, exception);
}
