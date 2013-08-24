#include "integer.h"

struct Integer {
    Type *type;
    Integer64 value;
};

static Integer *IntegerCreate(Integer64 value, VALUE **error) {
    Integer *integer = MemoryAlloc(sizeof(Integer), error);
    if (*error != NULL) {
        return NULL;
    }
    integer->type = TypeInteger;
    integer->value = value;
    return integer;
}

VALUE *IntegerDecode(Byte **bytes, VALUE **error) {
    Integer64 value = DecodeInteger64FLE(bytes);
    Integer *integer = IntegerCreate(value, error);
    return BridgeFromInteger(integer);
}

void IntegerDealloc(VALUE *integerValue) {
    MemoryDealloc(integerValue);
}

Integer64 IntegerHash(VALUE *integerValue) {
    return BridgeToInteger(integerValue)->value;
}

Bool IntegerEqual(VALUE *integerValue, VALUE *otherValue) {
    return BridgeToInteger(integerValue)->value == BridgeToInteger(otherValue)->value;
}

VALUE *IntegerSum(VALUE **args, Integer8 count, VALUE **error) {
    Integer *integer = BridgeToInteger(args[0]);
    Integer *other = BridgeToInteger(args[1]);
    Integer *result = IntegerCreate(integer->value + other->value, error);
    return BridgeFromInteger(result);
}
