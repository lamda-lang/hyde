#include "boolean.h"

struct Boolean {
    Value base;
    Integer64 hash;
}; 

static Boolean trueSingleton = {
    .base = TypeBoolean,
    .hash = 1234
};

static Boolean falseSingleton = {
    .base = TypeBoolean,
    .hash = 4321
};

Value *BooleanTrueSingleton(void) {
    return BridgeFromBoolean(&trueSingleton);
}

Value *BooleanFalseSingleton(void) {
    return BridgeFromBoolean(&falseSingleton);
}

Integer64 BooleanHash(Value *booleanValue) {
    return BridgeToBoolean(booleanValue)->hash;
}

Value *BooleanDecodeTrue(Byte **bytes, Error *error) {
    return BooleanTrueSingleton();
}

Value *BooleanDecodeFalse(Byte **bytes, Error *error) {
    return BooleanFalseSingleton();
}

Value *BooleanEval(Value *booleanValue, bool pure, Error *error) {
    return booleanValue;
}
