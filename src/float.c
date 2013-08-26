#include "float.h"

struct Float {
    Type *type;
    Float64 value;
};

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
    Float *fpv = FloatCreate(value, error);
    return BridgeFromFloat(fpv);
}

void FloatDealloc(VALUE *floatValue) {
    MemoryDealloc(floatValue);
}

Integer64 FloatHash(VALUE *floatValue) {
    return (Integer64)BridgeToFloat(floatValue)->value;
}

Bool FloatEqual(VALUE *floatValue, VALUE *otherValue) {
    return BridgeToFloat(floatValue)->value == BridgeToFloat(otherValue)->value;
}
