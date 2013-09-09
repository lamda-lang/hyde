#include <builtin/protocol.h>

typedef struct Signature Signature;
typedef struct Protocol Protocol;

struct Signature {
    Value *name;
    Value *arity;
};

struct Protocol {
    Value value;
    Integer32 count;
    Signature signatures[];
};

static Protocol *ProtocolCreate(Integer32 count, Error *error) {
    Protocol *protocol = MemoryAlloc(sizeof(Protocol) + sizeof(Signature) * count, error);
    if (*error != ErrorNone) return NULL;
    protocol->value = ValueProtocol;
    protocol->count = count;
    return protocol;
}

static Protocol *ProtocolDealloc(Protocol *protocol) {
    MemoryDealloc(protocol);
    return NULL;
}

Value *ProtocolDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Protocol *protocol = ProtocolCreate(count, error);
    if (*error != ErrorNone) return ProtocolDealloc(protocol);
    for (Integer32 index = 0; index < count; index += 1) {
        protocol->signatures[index].name = DecodeValue(bytes, error);
        if (*error != ErrorNone) return ProtocolDealloc(protocol);
        protocol->signatures[index].arity = DecodeValue(bytes, error);
        if (*error != ErrorNone) return ProtocolDealloc(protocol);
    }
    return protocol;
}

Bool ProtocolEqual(Value *protocolValue, Value *otherValue) {
}

void ProtocolDealloc(Value *protocolValue) {
    Protocol *protocol = protocolValue;
    ProtocolDealloc(protocol);
}
