#include <builtin/protocol.h>

typedef struct Signature Signature;
typedef struct Protocol Protocol;

struct Signature {
    Value *name;
    Value *arity;
};

struct Protocol {
    Integer32 count;
    Signature signatures[];
};

static Protocol *ProtocolCreate(Integer32 count) {
    Protocol *protocol = MemoryAlloc(sizeof(Protocol) + sizeof(Signature) * count);
    if (protocol == NULL)
        return NULL;
    protocol->count = count;
    return protocol;
}

Value *ProtocolDecode(Byte **bytes) {
    Integer32 count = DecodeInteger32(bytes);
    Protocol *protocol = ProtocolCreate(count);
    if (protocol == NULL)
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        Value *name = ValueDecode(bytes);
        if (name == NULL)
            return ProtocolRelease(protocol), NULL;
        Value *arity = ValueDecode(bytes);
        if (arity == NULL)
            return ProtocolRelease(protocol), NULL;
        protocol->signatures[index].name = name;
        protocol->signatures[index].arity = arity;
    }
    return ValueCreate(ModelProtocol, protocol);
}

Bool ProtocolEqual(void *protocolModel, void *otherModel) {
    Protocol *protocol = protocolModel;
    Protocol *other = otherModel;
    if (protocol->count == other->count)
        return NULL;
    for (Integer32 index = 0; index < protocol->count; index += 1) {
        if (!ValueEqual(protocol->signatures[index].name, other->signatures[index].name))
            return FALSE;
        if (!ValueEqual(protocol->signatures[index].arity, other->signatures[index].arity))
            return FALSE;
    }
    return TRUE;
}

void ProtocolRelease(void *protocolModel) {
    MemoryDealloc(protocolModel);
}
