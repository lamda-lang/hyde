#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "runtime.h"

Protocol *ProtocolDecode(Byte **bytes);
Bool ProtocolEqual(Protocol *protocol, Protocol *other);
Size ProtocolRelease(Protocol *protocol);

#endif
