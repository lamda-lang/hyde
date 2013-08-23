#include "nil.h"

struct Nil {
    Type *type;
};

static Nil nilSingleton = {
    .type = NULL
};

VALUE *NilSingleton(void) {
    return BridgeFromNil(&nilSingleton);
}

void *NilDecode(Byte **bytes, VALUE **error) {
    return &nilSingleton;
}

void NilDealloc(VALUE *nilVALUE) {
    MemoryDealloc(nilVALUE);
}

Integer64 NilHash(VALUE *nilVALUE) {
    return 1829;
}

Bool NilEqual(VALUE *nilVALUE, VALUE *otherVALUE) {
    return TRUE;
}
