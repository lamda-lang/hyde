#include "nil.h"

struct Nil {
    Type *type;
};

static Nil nilSingleton = {
    .type = NULL
};

Value *NilSingleton(void) {
    return BridgeFromNil(&nilSingleton);
}

void *NilDecode(Byte **bytes, Value **error) {
    return &nilSingleton;
}

void NilDealloc(Value *nilValue) {
    MemoryDealloc(nilValue);
}

Integer64 NilHash(Value *nilValue) {
    return 1829;
}

Bool NilEqual(Value *nilValue, Value *otherValue) {
    return TRUE;
}
