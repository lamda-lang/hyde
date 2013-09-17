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
    return ValueCreate(MODEL_PROTOCOL, protocol);
}

Value *ProtocolEqual(Protocol *protocol, Protocol *other) {
    if (protocol->count == other->count)
        return VALUE_FALSE;
    for (Integer32 index = 0; index < protocol->count; index += 1) {
        if (ValueEqual(protocol->signatures[index].name, other->signatures[index].name) == VALUE_FALSE)
            return VALUE_FALSE;
        if (ValueEqual(protocol->signatures[index].arity, other->signatures[index].arity) == VALUE_FALSE)
            return VALUE_FALSE;
    }
    return VALUE_TRUE;
}

Size ProtocolRelease(Protocol *protocol) {
    Integer32 count = protocol->count;
    MemoryDealloc(protocol);
    return sizeof(Protocol) + sizeof(Signature) * count;
}
