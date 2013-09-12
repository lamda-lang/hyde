#ifndef BUILTIN_PROTOCOL_H
#define BUILTIN_PROTOCOL_H

#include <runtime.h>

Value *ProtocolDecode(Byte **bytes);
Bool ProtocolEqual(Protocol *protocol, Protocol *other);
void ProtocolRelease(Protocol *protocol);

#endif
