#include "float.h"

struct Float {
    Value base;
    Float64 value;
};

static inline Float *Create(Float64 value, Error *error) {
    Float *fpv = MemoryAlloc(sizeof(Float), error);
    if (fpv == NULL) {
	goto returnError;
    }
    fpv->base = TypeFloat;
    fpv->value = value;
    return fpv;

returnError:
    return NULL;
}

Value *FloatDecode(Byte **bytes, Error *error) {
    Float64 value = DecodeFloat64FLE(bytes);
    Float *fpv = Create(value, error);
    return FloatValueBridge(fpv);
}

Value *FloatValueBridge(Float *fpv) {
    return (Value *)fpv;
}

void FloatDealloc(Value *floatValue) {
    MemoryDealloc(floatValue);
}

Integer64 FloatHash(Value *floatValue) {
    return (Integer64)ValueFloatBridge(floatValue)->value;
}

Float *FloatSum(Float *fpv, Float *other, Error *error) {
    Float64 sum = fpv->value + other->value;
    return Create(sum, error);
}

Value *FloatEval(Value *floatValue, bool pure, Error *error) {
    return floatValue;
}
