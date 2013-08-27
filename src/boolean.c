#include "boolean.h"

typedef struct {
    VALUE *type;
    Bool truth;
} Boolean; 

static Boolean *BooleanCreate(Bool truth, VALUE **error) {
    Boolean *boolean = MemoryAlloc(sizeof(Boolean), error);
    if (*error != NULL) {
        return NULL;
    }
    boolean->type = RuntimeBooleanType;
    boolean->truth = truth;
    return boolean;
}

VALUE *BooleanDecodeTrue(Byte **bytes, VALUE **error) {
    Boolean *true = BooleanCreate(TRUE, error);
    return true;
}

VALUE *BooleanDecodeFalse(Byte **bytes, VALUE **error) {
    Boolean *false = BooleanCreate(FALSE, error);
    return false;
}

void BooleanDealloc(VALUE *booleanValue) {
    MemoryDealloc(booleanValue);
}

Integer64 BooleanHash(VALUE *booleanValue) {
    Boolean *boolean = booleanValue;
    return boolean->truth;
}

Bool BooleanEqual(VALUE *booleanValue, VALUE *otherValue) {
    Boolean *boolean = booleanValue;
    Boolean *other = otherValue;
    return boolean->truth == other->truth;
}
