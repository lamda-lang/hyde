#include "boolean.h"

struct Boolean {
    Value base;
};

static Boolean trueSingleton = {
    .base = TypeBoolean
};

static Boolean falseSingleton = {
    .base = TypeBoolean
};

Value *BooleanValueBridge(Boolean *boolean) {
    return (Value *)boolean;
}

Boolean *BooleanTrueSingleton(void) {
    return &trueSingleton;
}

Boolean *BooleanFalseSingleton(void) {
    return &falseSingleton;
}

Integer64 BooleanHash(Value *boolean) {
    Boolean *booleanBridge = ValueBooleanBridge(boolean);
    return booleanBridge == &trueSingleton ? 1 : 0;
}
