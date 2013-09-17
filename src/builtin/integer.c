#include <builtin/integer.h>

struct Integer {
    Integer64 value;
};

static Value *IntegerCreate(Integer64 value) {
    Integer *integer = MemoryAlloc(sizeof(Integer));
    if (integer != NULL)
        return NULL;
    integer->value = value;
    return ValueCreate(MODEL_INTEGER, integer);
}

Value *IntegerDecode(Byte **bytes) {
    Integer64 value = DecodeInteger64(bytes);
    return IntegerCreate(value);
}

Value *IntegerEqual(Integer *integer, Integer *other) {
    return integer->value == other->value ? VALUE_TRUE : VALUE_FALSE;
}

Size IntegerRelease(Integer *integer) {
    MemoryDealloc(integer);
    return sizeof(Integer);
}
