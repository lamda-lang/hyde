#include "boolean.h"

struct Boolean {
    Value base;
    bool truth;
}; 

Value *BooleanCreate(bool truth, Error *error) {
    Boolean *boolean = MemoryAlloc(sizeof(Boolean), error);
    if (boolean == NULL) {
	goto returnError;
    }
    boolean->base = TypeBoolean;
    boolean->truth = truth;
    return BridgeFromBoolean(boolean);

returnError:
    return NULL;
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

Value *BooleanDecodeTrue(Byte **bytes, Error *error) {
    return GlobalBooleanTrue;
}

Value *BooleanDecodeFalse(Byte **bytes, Error *error) {
    return GlobalBooleanFalse;
}

Value *BooleanEval(Value *booleanValue, bool pure, Error *error) {
    return booleanValue;
}
