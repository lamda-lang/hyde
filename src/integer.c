#include "integer.h"

struct Integer {
    Integer64 value;
};

static Value *IntegerCreate(Integer64 value) {
    Integer *integer = MemoryAllocUnit(sizeof(Integer));
    integer->value = value;
    return ValueCreateInteger(integer);
}

Value *IntegerDecodePrimitive(Binary *binary, Integer32 *offset) {
    Integer64 value;
    if (BinaryDecodeInteger64(binary, offset, &value))
        return NULL;
    return IntegerCreate(value);
}
