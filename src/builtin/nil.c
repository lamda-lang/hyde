#include <builtin/nil.h>

typedef struct Nil Nil;

struct Nil {
    VALUE *type;
};

VALUE *NilCreate(Error *error) {
    Nil *nil = MemoryAlloc(sizeof(Nil), error);
    if (*error != ErrorNone) return NULL;
    nil->type = NULL;
    return nil;
}

VALUE *NilDecode(Byte **bytes, Error *error) {
    return NilCreate(error);
}

void NilDealloc(VALUE *nilValue) {
    MemoryDealloc(nilValue);
}
