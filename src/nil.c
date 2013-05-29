#include "nil.h"

struct Nil {
    Value base;
};

static Nil singleton = {
  .base = TypeNil
};

Nil *NilSingleton(void) {
    return &singleton;
}

Value *NilValueBridge(void) {
    return (Value *)&singleton;
}

Integer64 NilHash(Value *nilValue) {
    return 0;
}
