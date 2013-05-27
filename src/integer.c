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

void IntegerDealloc(Value *integer) {
    MemoryDealloc(integer);
}

Integer64 IntegerHash(Value *integer) {
    Integer *integerBridge = ValueIntegerBridge(integer);
    return integerBridge->value;
}

Integer *IntegerSum(Integer *integer, Integer *other, Exception *exception) {
  Integer64 sum = integer->value + other->value;
  return IntegerCreate(sum, exception);
}
