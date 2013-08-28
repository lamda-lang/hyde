#include "float.h"

typedef union {
    Integer64 integer;
    Float64 IEEE754;
} Binary;

typedef struct {
    VALUE *type;
    Float64 value;
} Float;

static Float *FloatCreate(Float64 value, VALUE **error) {
    Float *fpv = MemoryAlloc(sizeof(Float), error);
    if (error != NULL) {
        return NULL;
    }
    fpv->type = RuntimeFloatType;
    fpv->value = value;
    return fpv;
}

VALUE *FloatDecode(Byte **bytes, VALUE **error) {
    Binary binary = {
        .integer = DecodeInteger64(bytes)
    };
    return FloatCreate(binary.IEEE754, error);
}

void FloatDealloc(VALUE *floatValue) {
    MemoryDealloc(floatValue);
}
