#include <builtin/float.h>

typedef struct Float Float;
typedef union Binary Binary;

struct Float {
    VALUE *type;
    Float64 value;
};

union Binary {
    Integer64 integer;
    Float64 IEEE754;
};

static Float *FloatCreate(Float64 value, Error *error) {
    Float *fpv = MemoryAlloc(sizeof(Float), error);
    if (error != ErrorNone) return NULL;
    fpv->type = RuntimeValueForConstant(ConstantFloatType);
    fpv->value = value;
    return fpv;
}

VALUE *FloatDecode(Byte **bytes, Error *error) {
    Binary binary = {
        .integer = DecodeInteger64(bytes)
    };
    return FloatCreate(binary.IEEE754, error);
}

void FloatDealloc(VALUE *floatValue) {
    MemoryDealloc(floatValue);
}
