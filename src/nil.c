#include "nil.h"

struct Nil {
    Value base;
};

static Nil nilSingleton = {
    .base = TypeNil
};

Value *NilSingleton(void) {
    return BridgeFromNil(&nilSingleton);
}

void *NilDecode(Byte **bytes, Error *error) {
    return &nilSingleton;
}

Value *NilEval(void *data, Code *code, Value **context, Bool pure, Error *error) {
    return data;
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
