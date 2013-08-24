#include "boolean.h"

struct Boolean {
    Type *type;
    Bool truth;
}; 

static Boolean *BooleanCreate(Bool truth, VALUE **error) {
    Boolean *boolean = MemoryAlloc(sizeof(Boolean), error);
    if (*error != NULL) {
        return NULL;
    }
    boolean->type = TypeBoolean;
    boolean->truth = truth;
    return boolean;
}

VALUE *BooleanDecodeTrue(Byte **bytes, VALUE **error) {
    Boolean *true = BooleanCreate(TRUE, error);
    return BridgeFromBoolean(true);
}

VALUE *BooleanDecodeFalse(Byte **bytes, VALUE **error) {
    Boolean *false = BooleanCreate(FALSE, error);
    return BridgeFromBoolean(false);
}

void BooleanDealloc(VALUE *booleanValue) {
    MemoryDealloc(booleanValue);
}

Integer64 BooleanHash(VALUE *booleanValue) {
    return BridgeToBoolean(booleanValue)->truth;
}

Bool BooleanEqual(VALUE *booleanValue, VALUE *otherValue) {
    return BridgeToBoolean(booleanValue)->truth == BridgeToBoolean(otherValue)->truth;
}
