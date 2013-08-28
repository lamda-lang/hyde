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

static Protocol *ProtocolCreate(Integer32 count, VALUE **error) {
    Protocol *protocol = MemoryAlloc(sizeof(Protocol) + sizeof(Signature) * count, error);
    if (*error != NULL) {
        return NULL;
    }
    protocol->type = RuntimeProtocolType;
    protocol->count = count;
    return protocol;
}

VALUE *ProtocolDecode(Byte **bytes, VALUE **error) {
    Integer32 count = DecodeInteger32(bytes);
    Protocol *protocol = ProtocolCreate(count, error);
    if (*error != NULL) {
        goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
        protocol->signatures[index].name = DecodeValue(bytes, error);
        if (*error != NULL) {
            goto deallocProtocol;
        }
        protocol->signatures[index].arity = DecodeValue(bytes, error);
        if (*error != NULL) {
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
