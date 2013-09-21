#include "integer.h"

struct Integer {
    Integer64 value;
};

static Integer *IntegerCreate(Integer64 value) {
    Integer *integer = MemoryAlloc(sizeof(Integer));
    if (integer != NULL)
        return NULL;
    integer->value = value;
    return integer;
}

Integer *IntegerDecode(Byte **bytes) {
    Integer64 value = DecodeInteger64(bytes);
    return IntegerCreate(value);
}

Bool IntegerEqual(Integer *integer, Integer *other) {
    return integer->value == other->value;
}

Size IntegerRelease(Integer *integer) {
    MemoryDealloc(integer);
    return sizeof(Integer);
}
