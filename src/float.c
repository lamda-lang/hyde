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

Value *FloatEval(Value *floatValue, bool pure, Error *error) {
    return floatValue;
}
