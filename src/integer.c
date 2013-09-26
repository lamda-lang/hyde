#include "integer.h"

struct Integer {
    Integer64 value;
};

static Integer *IntegerCreate(Integer64 value, Error *error) {
    Integer *integer = MemoryAlloc(sizeof(Integer), error);
    if (ERROR(error))
        return NULL;
    integer->value = value;
    return integer;
}

Size IntegerSize(Integer *integer) {
    return INTEGER_64_SIZE;
}

Size IntegerEncode(Integer *integer, Byte **bytes) {
    EncodeInteger64(integer->value, bytes);
    return IntegerSize(integer);
}

Integer *IntegerDecode(Byte **bytes, Error *error) {
    Integer64 value = DecodeInteger64(bytes);
    return IntegerCreate(value, error);
}

Bool IntegerEqual(Integer *integer, Integer *other) {
    return integer->value == other->value;
}

Size IntegerRelease(Integer *integer) {
    MemoryDealloc(integer);
    return sizeof(Integer);
}
