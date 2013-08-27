#include "protocol.h"

struct Protocol {
    Type *type;
    Integer32 count;
};

static Protocol *ProtocolCreate(Integer32 count, VALUE **error) {
    Protocol *protocol = MemoryAlloc(sizeof(Protocol), error);
    if (*error != NULL) {
        return NULL;
    }
    protocol->type = RuntimeProtocolType;
    protocol->count = count;
    return protocol;
}

VALUE *ProtocolDecode(Byte **bytes, VALUE **error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Protocol *protocol = ProtocolCreate(count, error);
    if (*error != NULL) {
        goto returnError;
    }
    return BridgeFromProtocol(protocol);

returnError:
    return NULL;
}
