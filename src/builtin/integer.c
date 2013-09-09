#include <builtin/integer.h>

typedef struct Integer Integer;

struct Integer {
    Integer64 value;
};

static Integer *IntegerCreate(Integer64 value, Error *error) {
    Integer *integer = MemoryAlloc(sizeof(Integer), error);
    if (*error != ErrorNone)
        return NULL;
    integer->value = value;
    return integer;
}

static void IntegerDealloc(Integer *integer) {
    MemoryDealloc(integer);
}

Value *IntegerDecode(Byte **bytes, Error *error) {
    Integer64 value = DecodeInteger64(bytes);
    Integer *integer = IntegerCreate(value, error);
    if (*error != ErrorNone)
        return NULL;
    return ValueCreate(BuiltinInteger, integer);
}

Bool IntegerEqual(void *integerModel, void *otherModel) {
    Integer *integer = integerModel;
    Integer *other = otherModel;
    return integer->value == otherValue;
}

void IntegerRelease(void *integerModel) {
    IntegerDealloc(integerModel);
}
