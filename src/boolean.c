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

static Value *ValueBridge(Boolean *boolean) {
    return (Value *)boolean;
}

Value *BooleanTrueSingleton(void) {
    return ValueBridge(&trueSingleton);
}

Value *BooleanFalseSingleton(void) {
    return ValueBridge(&falseSingleton);
}

Integer64 BooleanHash(Value *booleanValue) {
    return ValueBooleanBridge(booleanValue, NULL)->hash;
}

Value *BooleanDecodeTrue(Byte **bytes, Error *error) {
    return BooleanTrueSingleton();
}

Value *BooleanDecodeFalse(Byte **bytes, Error *error) {
    return BooleanFalseSingleton();
}
