#include "lamda.h"

typedef struct {
    Integer8 arity;
    Integer8 count;
    Integer32 context[];
} Model;

struct Lamda {
    Type  *type;
    Integer8 arity;
    Integer8 count;
    VALUE *context[];
};

static Lamda *Create(Integer8 arity, Integer8 count, VALUE **error) {
    Lamda *lamda = MemoryAlloc(sizeof(Lamda) + sizeof(VALUE *) * count, error);
    if (lamda == NULL) {
        goto returnVALUE;
    }
    lamda->type = TypeLamda;
    lamda->arity = arity;
    lamda->count = count;
    return lamda;

returnVALUE:
    return NULL;
}

VALUE *LamdaDecode(Byte **bytes, VALUE **error) {
    return NULL;
}

void LamdaDealloc(VALUE *lamdaVALUE) {
    MemoryDealloc(lamdaVALUE);
}

Integer64 LamdaHash(VALUE *lamdaVALUE) {
    return BridgeToLamda(lamdaVALUE)->arity;
}

Integer8 LamdaArity(VALUE *lamdaVALUE) {
    return BridgeToLamda(lamdaVALUE)->arity;
}

void LamdaEnumerate(VALUE *lamdaVALUE, void (*callback)(VALUE *value)) {
    Lamda *lamda = BridgeToLamda(lamdaVALUE);
    for (Integer8 index = 0; index < lamda->count; index += 1) {
        callback(lamda->context[index]);
    }
}

VALUE **LamdaCreateContext(VALUE *lamdaVALUE, VALUE **error) {
    Lamda *lamda = BridgeToLamda(lamdaVALUE);
    return MemoryAlloc(sizeof(VALUE *) * (lamda->arity + lamda->count), error);
}

void LamdaDeallocContext(VALUE **context) {
    MemoryDealloc(context);
}
