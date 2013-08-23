#include "boolean.h"

struct Boolean {
    Type *type;
    Bool truth;
}; 

static Boolean trueSingleton = {
    .truth = TRUE
};

static Boolean falseSingleton = {
    .truth = FALSE
};

Value *BooleanTrueSingleton(void) {
    return BridgeFromBoolean(&trueSingleton);
}

Value *BooleanFalseSingleton(void) {
    return BridgeFromBoolean(&falseSingleton);
}

void *BooleanDecodeTrue(Byte **bytes, Value **error) {
    return &trueSingleton;
}

void *BooleanDecodeFalse(Byte **bytes, Value **error) {
    return &falseSingleton;
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
