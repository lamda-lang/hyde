#include "boolean.h"

typedef struct {
    VALUE *type;
    Bool truth;
} Boolean; 

static Boolean *BooleanCreate(Bool truth, Error *error) {
    Boolean *boolean = MemoryAlloc(sizeof(Boolean), error);
    if (*error != ErrorNone) {
        return NULL;
    }
    boolean->type = NULL;
    boolean->truth = truth;
    return boolean;
}

VALUE *BooleanDecodeTrue(Byte **bytes, Error *error) {
    Boolean *true = BooleanCreate(TRUE, error);
    return true;
}

VALUE *BooleanDecodeFalse(Byte **bytes, Error *error) {
    Boolean *false = BooleanCreate(FALSE, error);
    return false;
}

void BooleanDealloc(VALUE *booleanValue) {
    MemoryDealloc(booleanValue);
}
