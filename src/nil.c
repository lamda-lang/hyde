#include "nil.h"

struct Nil {
    Value base;
    Integer64 hash;
};

static Nil nilSingleton = {
    .base = TypeNil,
    .hash = 1827
};

static Value *ValueBridge(Nil *nil) {
    return (Value *)nil;
}

Value *NilSingleton(void) {
    return ValueBridge(&nilSingleton);
}

Integer64 NilHash(Value *nilValue) {
    return ValueNilBridge(nilValue, NULL)->hash;
}

Value *NilDecode(Byte **bytes, Error *error) {
    return NilSingleton();
}
