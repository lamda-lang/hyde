#include <builtin/nil.h>

typedef struct Nil Nil;

struct Nil {
    Value *type;
};

static Nil NilConstantValue = {
    .value = ValueNil
};

Value *NilConstant(void) {
    return &NilConstantValue;

Value *NilDecode(Byte **bytes, Error *error) {
    return &NilConstantValue;
}

Bool NilEqual(Value *nilValue, Value *otherValue) {
    return TRUE;
}
