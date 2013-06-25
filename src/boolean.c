#include "boolean.h"

struct Boolean {
    Value base;
    bool truth;
}; 

static Boolean trueSingleton = {
    .base = TypeBoolean,
    .truth = true
};

static Boolean falseSingleton = {
    .base = TypeBoolean,
    .truth = false
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

Value *BooleanEval(void *data, Code *code, Value **context, bool pure, Error *error) {
    return data;
}

void BooleanDealloc(Value *booleanValue) {
    MemoryDealloc(booleanValue);
}

Integer64 BooleanHash(Value *booleanValue) {
    return BridgeToBoolean(booleanValue)->truth;
}

bool BooleanEqual(Value *booleanValue, Value *otherValue) {
    return BridgeToBoolean(booleanValue)->truth == BridgeToBoolean(otherValue)->truth;
}
