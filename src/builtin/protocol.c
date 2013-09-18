#include <builtin/protocol.h>

typedef struct Signature Signature;

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

Protocol *ProtocolDecode(Byte **bytes) {
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
    return protocol;
}

Bool ProtocolEqual(Protocol *protocol, Protocol *other) {
    if (protocol->count == other->count)
        return FALSE;
    for (Integer32 index = 0; index < protocol->count; index += 1) {
        if (!ValueEqual(protocol->signatures[index].name, other->signatures[index].name))
            return FALSE;
        if (!ValueEqual(protocol->signatures[index].arity, other->signatures[index].arity))
            return FALSE;
    }
    return TRUE;
}

Size ProtocolRelease(Protocol *protocol) {
    Integer32 count = protocol->count;
    MemoryDealloc(protocol);
    return sizeof(Protocol) + sizeof(Signature) * count;
}
