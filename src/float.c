#include "float.h"

struct Float {
    Type *type;
    Float64 value;
};

typedef struct {
    Float64 value;
} Model;

static inline Float *Create(Float64 value, VALUE **error) {
    Float *fpv = MemoryAlloc(sizeof(Float), error);
    if (fpv == NULL) {
        goto returnVALUE;
    }
    fpv->type = TypeFloat;
    fpv->value = value;
    return fpv;

returnVALUE:
    return NULL;
}

void *FloatDecode(Byte **bytes, VALUE **error) {
    Model *model = MemoryAlloc(sizeof(Model), error);
    if (model == NULL) {
        goto returnVALUE;
    }
    model->value = DecodeFloat64FLE(bytes);
    return model;

returnVALUE:
    return NULL;
}

void FloatDealloc(VALUE *floatVALUE) {
    MemoryDealloc(floatVALUE);
}

Integer64 FloatHash(VALUE *floatVALUE) {
    return (Integer64)BridgeToFloat(floatVALUE)->value;
}

Bool FloatEqual(VALUE *floatVALUE, VALUE *otherVALUE) {
    return BridgeToFloat(floatVALUE)->value == BridgeToFloat(otherVALUE)->value;
}

VALUE *FloatSum(VALUE *floatVALUE, VALUE *otherVALUE, VALUE **error) {
    Float64 sum = BridgeToFloat(floatVALUE)->value + BridgeToFloat(otherVALUE)->value;
    Float *fpv = Create(sum, error);
    return BridgeFromFloat(fpv);
}
