#include <builtin/boolean.h>

typedef struct Boolean Boolean;

struct Boolean {
    VALUE *type;
    Bool truth;
}; 

VALUE *BooleanCreate(Bool truth, Error *error) {
    Boolean *boolean = MemoryAlloc(sizeof(Boolean), error);
    if (*error != ErrorNone) return NULL;
    boolean->type = RuntimeValueForConstant(ConstantBooleanType);
    boolean->truth = truth;
    return boolean;
}

VALUE *BooleanDecodeTrue(Byte **bytes, Error *error) {
    return RuntimeValueForConstant(ConstantTrue);
}

VALUE *BooleanDecodeFalse(Byte **bytes, Error *error) {
    return RuntimeValueForConstant(ConstantFalse);
}

void BooleanDealloc(VALUE *booleanValue) {
    MemoryDealloc(booleanValue);
}
