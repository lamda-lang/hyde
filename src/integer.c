#include "integer.h"

struct Integer {
    Integer64 value;
};

static Value *IntegerCreate(Integer64 value) {
    Integer *integer = MemoryAllocUnit(sizeof(Integer));
    integer->value = value;
    return ValueCreateInteger(integer);
}

Bool IntegerDecode(Binary *binary, Integer32 *offset, Value **value) {
    Integer64 data;
    if (!BinaryDecodeInteger64(binary, offset, &data))
        return FALSE;
    *value = IntegerCreate(data);
    return TRUE;
}
