#include "boolean.h"

struct Boolean {
    Value base;
    Bool truth;
}; 

static Boolean trueSingleton = {
    .base = TypeBoolean,
    .truth = TRUE
};

static Boolean falseSingleton = {
    .base = TypeBoolean,
    .truth = FALSE
};

Value *BooleanTrueSingleton(void) {
    return BridgeFromBoolean(&trueSingleton);
}

Value *BooleanFalseSingleton(void) {
    return BridgeFromBoolean(&falseSingleton);
}

void *BooleanDecodeTrue(Byte **bytes, Error *error) {
    return &trueSingleton;
}

void *BooleanDecodeFalse(Byte **bytes, Error *error) {
    return &falseSingleton;
}

Value *BooleanEval(void *data, Code *code, Value **context, Bool pure, Error *error) {
    return data;
}

void BooleanDealloc(Value *booleanValue) {
    MemoryDealloc(booleanValue);
}

Integer64 BooleanHash(Value *booleanValue) {
    return BridgeToBoolean(booleanValue)->truth;
}

Bool BooleanEqual(Value *booleanValue, Value *otherValue) {
    return BridgeToBoolean(booleanValue)->truth == BridgeToBoolean(otherValue)->truth;
}
