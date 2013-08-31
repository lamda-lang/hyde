#include "nil.h"

typedef struct {
    VALUE *type;
} Nil;

VALUE *NilDecode(Byte **bytes, Error *error) {
    Nil *nil = MemoryAlloc(sizeof(Nil), error);
    if (*error != ErrorNone) {
        return NULL;
    }
    nil->type = NULL;
    return nil;
}

void NilDealloc(VALUE *nilValue) {
    MemoryDealloc(nilValue);
}
