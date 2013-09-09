#include <builtin/integer.h>

typedef struct Integer Integer;

struct Integer {
    Value value;
    Integer64 value;
};

static Integer *IntegerCreate(Integer64 value, Error *error) {
    Integer *integer = MemoryAlloc(sizeof(Integer), error);
    if (*error != ErrorNone) return NULL;
    integer->value = ValueInteger;
    integer->value = value;
    return integer;
}

static Integer *IntegerDealloc(Integer *integer) {
    MemoryDealloc(integer);
    return NULL;
}

Value *IntegerDecode(Byte **bytes, Error *error) {
    Integer64 value = DecodeInteger64(bytes);
    return IntegerCreate(value, error);
}

Bool IntegerEqual(Value *integerValue, Value *otherValue) {
    if (integerValue == otherValue) return TRUE;
    Integer *integer = integerValue;
    Integer *other = otherValue;
    return integer->value == other->value;
}

void IntegerRelease(Value *integerValue) {
    IntegerDealloc(integer);
}
