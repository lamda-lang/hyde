#include <builtin/protocol.h>

/* type */
typedef struct Signature Signature;
typedef struct Protocol Protocol;

struct Signature {
    VALUE *name;
    VALUE *arity;
};

struct Protocol {
    VALUE *type;
    Integer32 count;
    Signature signatures[];
};

/* private */
static Protocol *ProtocolCreate(Integer32 count, Error *error) {
    Protocol *protocol = MemoryAlloc(sizeof(Protocol) + sizeof(Signature) * count, error);
    if (*error != ErrorNone) return NULL;
    protocol->type = NULL;
    protocol->count = count;
    return protocol;
}

/* public */
VALUE *ProtocolDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Protocol *protocol = ProtocolCreate(count, error);
    if (*error != ErrorNone) goto returnError;
    for (Integer32 index = 0; index < count; index += 1) {
        protocol->signatures[index].name = DecodeValue(bytes, error);
        if (*error != ErrorNone) goto deallocProtocol;
        protocol->signatures[index].arity = DecodeValue(bytes, error);
        if (*error != ErrorNone) goto deallocProtocol;
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
