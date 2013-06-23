#include "float.h"

struct Float {
    Value base;
    Float64 value;
};

typedef struct {
    Float64 value;
} Model;

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

void *FloatDecode(Byte **bytes, Error *error) {
    Model *model = MemoryAlloc(sizeof(Model), error);
    if (model == NULL) {
	goto returnError;
    }
    model->value = DecodeFloat64FLE(bytes);
    return model;

returnError:
    return NULL;
}

Value *FloatEval(void *data, Code *code, bool pure, Error *error) {
    Model *model = data;
    Float *fpv = Create(model->value, error);
    return BridgeFromFloat(fpv);
}

void FloatDealloc(Value *floatValue) {
    MemoryDealloc(floatValue);
}

Integer64 FloatHash(Value *floatValue) {
    return (Integer64)BridgeToFloat(floatValue)->value;
}

bool FloatEqual(Value *floatValue, Value *otherValue) {
    return BridgeToFloat(floatValue)->value == BridgeToFloat(otherValue)->value;
}

Value *FloatSum(Value *floatValue, Value *otherValue, Error *error) {
    Float64 sum = BridgeToFloat(floatValue)->value + BridgeToFloat(otherValue)->value;
    Float *fpv = Create(sum, error);
    return BridgeFromFloat(fpv);
}
