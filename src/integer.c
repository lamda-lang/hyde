#include "integer.h"

typedef struct {
    VALUE *type;
    Integer64 value;
} Integer;

static Integer *IntegerCreate(Integer64 value, VALUE **error) {
    Integer *integer = MemoryAlloc(sizeof(Integer), error);
    if (*error != NULL) {
        return NULL;
    }
    integer->type = RuntimeIntegerType;
    integer->value = value;
    return integer;
}

VALUE *IntegerDecode(Byte **bytes, VALUE **error) {
    Integer64 value = DecodeInteger64FLE(bytes);
    return IntegerCreate(value, error);
}

void IntegerDealloc(VALUE *integerValue) {
    MemoryDealloc(integerValue);
}

Integer64 IntegerHash(VALUE *integerValue) {
    Integer *integer = integerValue;
    return integer->value;
}

Bool IntegerEqual(VALUE *integerValue, VALUE *otherValue) {
    Integer *integer = integerValue;
    Integer *other = integerValue;
    return integer->value == other->value;
}

VALUE *IntegerSum(VALUE **args, Integer8 count, VALUE **error) {
    Integer *integer = args[0];
    Integer *other = args[1];
    return IntegerCreate(integer->value + other->value, error);
}
