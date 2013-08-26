#include "lamda.h"

struct Lamda {
    Type  *type;
    Integer8 arity;
    Integer8 count;
    VALUE *result;
    VALUE *upvalues[];
};

static Lamda *LamdaCreate(VALUE *result, Integer8 arity, Integer8 count, VALUE **error) {
    Lamda *lamda = MemoryAlloc(sizeof(Lamda) + sizeof(VALUE *) * count, error);
    if (*error != NULL) {
        return NULL;
    }
    lamda->type = TypeLamda;
    lamda->arity = arity;
    lamda->count = count;
    lamda->result = result;
    return lamda;
}

VALUE *LamdaDecode(Byte **bytes, VALUE **error) {
    Integer8 arity = DecodeInteger8FLE(bytes);
    Integer8 count = DecodeInteger8FLE(bytes);
    VALUE *result = DecodeValue(bytes, error);
    if (*error != NULL) {
        goto returnError;
    }
    Lamda *lamda = LamdaCreate(result, arity, count, error);
    if (*error != NULL) {
        goto returnError;
    }
    for (Integer8 index = 0; index < count; index += 1) {
        lamda->upvalues[index] = DecodeValue(bytes, error);
        if (*error != NULL) {
            goto deallocLamda;
        }
    }
    return BridgeFromLamda(lamda);

deallocLamda:
    MemoryDealloc(lamda);
returnError:
    return NULL;
}

void LamdaDealloc(VALUE *lamdaValue) {
    MemoryDealloc(lamdaValue);
}

Integer64 LamdaHash(VALUE *lamdaValue) {
    Lamda *lamda = BridgeToLamda(lamdaValue);
    return lamda->arity + lamda->count;
}
