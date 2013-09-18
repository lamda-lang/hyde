#ifndef BUILTIN_PROTOCOL_H
#define BUILTIN_PROTOCOL_H

#include <runtime.h>

typedef struct Protocol Protocol;

Protocol *ProtocolDecode(Byte **bytes);
Value *ProtocolEqual(Protocol *protocol, Protocol *other);
Size ProtocolRelease(Protocol *protocol);

#endif
