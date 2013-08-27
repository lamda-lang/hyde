#include "nil.h"

typedef struct {
    VALUE *type;
} Nil;

VALUE *NilDecode(Byte **bytes, VALUE **error) {
    Nil *nil = MemoryAlloc(sizeof(Nil), error);
    if (*error != NULL) {
        return NULL;
    }
    nil->type = RuntimeNilType;
    return nil;
}

void NilDealloc(VALUE *nilValue) {
    MemoryDealloc(nilValue);
}
