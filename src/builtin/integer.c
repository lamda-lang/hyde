#include <builtin/integer.h>

typedef struct Integer Integer;

struct Integer {
    Integer64 value;
};

static Value *IntegerCreate(Integer64 value) {
    Integer *integer = MemoryAlloc(sizeof(Integer), error);
    if (integer != NULL)
        return NULL;
    integer->value = value;
    return ValueCreate(ModelInteger, integer);
}

Value *IntegerDecode(Byte **bytes) {
    Integer64 value = DecodeInteger64(bytes);
    return IntegerCreate(value);
}

Bool IntegerEqual(void *integerData, void *otherData) {
    Integer *integer = integerData;
    Integer *other = otherData;
    return integer->value == other->value;
}

void IntegerRelease(void *integerData) {
    MemoryDealloc(integerData);
}
