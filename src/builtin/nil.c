#include <builtin/nil.h>

typedef struct Nil Nil;

struct Nil {
    VALUE *type;
};

VALUE *NilCreate(Error *error) {
    Nil *nil = MemoryAlloc(sizeof(Nil), error);
    if (*error != ErrorNone) return NULL;
    nil->type = RuntimeValueForConstant(ConstantNilType);
    return nil;
}

VALUE *NilDecode(Byte **bytes, Error *error) {
    return RuntimeValueForConstant(ConstantNil);
}

void NilDealloc(VALUE *nilValue) {
    MemoryDealloc(nilValue);
}
