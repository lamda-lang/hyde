#include "boolean.h"

struct Boolean {
    Type *type;
    Bool truth;
}; 

void BooleanDealloc(VALUE *booleanVALUE) {
    MemoryDealloc(booleanVALUE);
}

Integer64 BooleanHash(VALUE *booleanVALUE) {
    return BridgeToBoolean(booleanVALUE)->truth;
}

Bool BooleanEqual(VALUE *booleanVALUE, VALUE *otherVALUE) {
    return BridgeToBoolean(booleanVALUE)->truth == BridgeToBoolean(otherVALUE)->truth;
}
