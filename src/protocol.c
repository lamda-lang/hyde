#include "protocol.h"

typedef struct Signature Signature;

struct Signature {
    Value *name;
    Value *arity;
};

struct Protocol {
    Integer32 count;
    Signature signatures[];
};

static Size ProtocolSize(Integer32 count) {
    return sizeof(Protocol) + sizeof(Signature) * count;
}

static Protocol *ProtocolCreate(Integer32 count, Error *error) {
    Size size = ProtocolSize(count);
    Protocol *protocol = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    protocol->count = count;
    return protocol;
}

Protocol *ProtocolDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Protocol *protocol = ProtocolCreate(count, error);
    if (ERROR(error))
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        protocol->signatures[index].name = ValueDecode(bytes, error);
        if (ERROR(error))
            goto protocol;
        protocol->signatures[index].arity = ValueDecode(bytes, error);
        if (ERROR(error))
            goto protocol;
    }
    return protocol;

protocol:
    ProtocolRelease(protocol);
    return NULL;
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
    Size size = ProtocolSize(protocol->count);
    MemoryDealloc(protocol);
    return size;
}
