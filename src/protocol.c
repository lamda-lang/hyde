#include "protocol.h"

typedef struct {
    VALUE *name;
    VALUE *arity;
} Signature;

typedef struct {
    VALUE *type;
    Integer32 count;
    Signature signatures[];
} Protocol;

static Protocol *ProtocolCreate(Integer32 count, Error *error) {
    Protocol *protocol = MemoryAlloc(sizeof(Protocol) + sizeof(Signature) * count, error);
    if (*error != ErrorNone) {
        return NULL;
    }
    protocol->type = NULL;
    protocol->count = count;
    return protocol;
}

VALUE *ProtocolDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Protocol *protocol = ProtocolCreate(count, error);
    if (*error != ErrorNone) {
        goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
        protocol->signatures[index].name = DecodeValue(bytes, error);
        if (*error != ErrorNone) {
            goto deallocProtocol;
        }
        protocol->signatures[index].arity = DecodeValue(bytes, error);
        if (*error != ErrorNone) {
            goto deallocProtocol;
        }
    }
    return protocol;

deallocProtocol:
    ProtocolDealloc(protocol);
returnError:
    return NULL;
}

void ProtocolDealloc(VALUE *protocolValue) {
    MemoryDealloc(protocolValue);
}
