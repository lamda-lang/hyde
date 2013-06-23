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

void *BooleanDecodeTrue(Byte **bytes, Error *error) {
    return GlobalBooleanTrue;
}

void *BooleanDecodeFalse(Byte **bytes, Error *error) {
    return GlobalBooleanFalse;
}

Value *BooleanEval(void *data, Code *code, bool pure, Error *error) {
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
