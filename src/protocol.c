#include "protocol.h"

typedef struct {
    VALUE *type;
    Integer32 count;
} Protocol;

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
    Integer32 count = DecodeInteger32(bytes);
    Protocol *protocol = ProtocolCreate(count, error);
    if (*error != NULL) {
        goto returnError;
    }
    return protocol;

returnError:
    return NULL;
}
