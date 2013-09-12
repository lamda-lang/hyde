#ifndef BUILTIN_PROTOCOL_H
#define BUILTIN_PROTOCOL_H

#include <runtime.h>

Value *ProtocolDecode(Byte **bytes);
Bool ProtocolEqual(void *protocolData, void *otherData);
void ProtocolRelease(void *protocolData);

#endif
