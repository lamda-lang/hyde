#include "integer.h"

typedef struct {
    VALUE *type;
    Integer64 value;
} Integer;

static Integer *IntegerCreate(Integer64 value, Error *error) {
    Integer *integer = MemoryAlloc(sizeof(Integer), error);
    if (*error != NULL) {
        return NULL;
    }
    integer->type = RuntimeIntegerType;
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
