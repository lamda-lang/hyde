#include "nil.h"

struct Nil {
    Value base;
    Integer64 hash;
};

static Nil nilSingleton = {
    .base = TypeNil,
    .hash = 1827
};

Value *NilSingleton(void) {
    return BridgeFromNil(&nilSingleton);
}

Integer64 NilHash(Value *nilValue) {
    return BridgeToNil(nilValue)->hash;
}

Value *NilDecode(Byte **bytes, Error *error) {
    return NilSingleton();
}

Value *NilEval(Value *nilValue, bool pure, Error *error) {
    return nilValue;
}
