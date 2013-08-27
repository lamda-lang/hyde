#include "float.h"

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
    Float64 value = DecodeFloat64FLE(bytes);
    return FloatCreate(value, error);
}

void FloatDealloc(VALUE *floatValue) {
    MemoryDealloc(floatValue);
}

Integer64 FloatHash(VALUE *floatValue) {
    Float *fpv = floatValue;
    return (Integer64)fpv->value;
}

Bool FloatEqual(VALUE *floatValue, VALUE *otherValue) {
    Float *fpv = floatValue;
    Float *other = floatValue;
    return fpv->value == other->value;
}
