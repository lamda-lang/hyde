#include "nil.h"

struct Nil {
    Type *type;
};

VALUE *NilDecode(Byte **bytes, VALUE **error) {
    Nil *nil = MemoryAlloc(sizeof(Nil), error);
    return BridgeFromNil(nil);
}

void NilDealloc(VALUE *nilValue) {
    MemoryDealloc(nilValue);
}

Integer64 NilHash(VALUE *nilValue) {
    return 27102011;
}

Bool NilEqual(VALUE *nilValue, VALUE *otherValue) {
    return TRUE;
}
