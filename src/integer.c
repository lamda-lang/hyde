#include "integer.h"

typedef struct Integer Integer;

struct Integer {
    VALUE *type;
    Integer64 value;
};

static Integer *IntegerCreate(Integer64 value, Error *error) {
    Integer *integer = MemoryAlloc(sizeof(Integer), error);
    if (*error != ErrorNone) return NULL;
    integer->type = RuntimeValueForConstant(ConstantIntegerType);
    integer->value = value;
    return integer;
}

VALUE *IntegerDecode(Byte **bytes, Error *error) {
    Integer64 value = DecodeInteger64(bytes);
    return IntegerCreate(value, error);
}

void IntegerDealloc(VALUE *integerValue) {
    MemoryDealloc(integerValue);
}
