#include <builtin/boolean.h>

typedef struct Boolean Boolean;

struct Boolean {
    VALUE *type;
    Bool truth;
}; 

VALUE *BooleanCreate(Bool truth, Error *error) {
    Boolean *boolean = MemoryAlloc(sizeof(Boolean), error);
    if (*error != ErrorNone) return NULL;
    boolean->type = NULL;
    boolean->truth = truth;
    return boolean;
}

VALUE *BooleanDecodeTrue(Byte **bytes, Error *error) {
    return BooleanCreate(TRUE, error);
}

VALUE *BooleanDecodeFalse(Byte **bytes, Error *error) {
    return BooleanCreate(FALSE, error);
}

void BooleanDealloc(VALUE *booleanValue) {
    MemoryDealloc(booleanValue);
}
