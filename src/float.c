#include "float.h"

struct Float {
    Type *type;
    Float64 value;
};

typedef struct {
    Float64 value;
} Model;

static inline Float *Create(Float64 value, Value **error) {
    Float *fpv = MemoryAlloc(sizeof(Float), error);
    if (fpv == NULL) {
        goto returnValue;
    }
    fpv->type = TypeFloat;
    fpv->value = value;
    return fpv;

returnValue:
    return NULL;
}

void *FloatDecode(Byte **bytes, Value **error) {
    Model *model = MemoryAlloc(sizeof(Model), error);
    if (model == NULL) {
        goto returnValue;
    }
    model->value = DecodeFloat64FLE(bytes);
    return model;

returnValue:
    return NULL;
}

void FloatDealloc(Value *floatValue) {
    MemoryDealloc(floatValue);
}

Integer64 FloatHash(Value *floatValue) {
    return (Integer64)BridgeToFloat(floatValue)->value;
}

Bool FloatEqual(Value *floatValue, Value *otherValue) {
    return BridgeToFloat(floatValue)->value == BridgeToFloat(otherValue)->value;
}

Value *FloatSum(Value *floatValue, Value *otherValue, Value **error) {
    Float64 sum = BridgeToFloat(floatValue)->value + BridgeToFloat(otherValue)->value;
    Float *fpv = Create(sum, error);
    return BridgeFromFloat(fpv);
}
