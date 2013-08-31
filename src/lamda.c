#include "lamda.h"

typedef struct {
    VALUE *type;
    VALUE *result;
    Integer8 arity;
    Integer8 count;
    VALUE *upvalues[];
} Lamda;

static Lamda *LamdaCreate(VALUE *result, Integer8 arity, Integer8 count, Error *error) {
    Lamda *lamda = MemoryAlloc(sizeof(Lamda) + sizeof(VALUE *) * count, error);
    if (*error != ErrorNone) {
        return NULL;
    }
    lamda->type = NULL;
    lamda->arity = arity;
    lamda->count = count;
    lamda->result = result;
    return lamda;
}

VALUE *LamdaDecode(Byte **bytes, Error *error) {
    Integer8 arity = DecodeInteger8(bytes);
    Integer8 count = DecodeInteger8(bytes);
    VALUE *result = DecodeValue(bytes, error);
    if (*error != ErrorNone) {
        goto returnError;
    }
    Lamda *lamda = LamdaCreate(result, arity, count, error);
    if (*error != ErrorNone) {
        goto returnError;
    }
    for (Integer8 index = 0; index < count; index += 1) {
        lamda->upvalues[index] = DecodeValue(bytes, error);
        if (*error != ErrorNone) {
            goto deallocLamda;
        }
    }
    return lamda;

deallocLamda:
    MemoryDealloc(lamda);
returnError:
    return NULL;
}

void LamdaDealloc(VALUE *lamdaValue) {
    MemoryDealloc(lamdaValue);
}
