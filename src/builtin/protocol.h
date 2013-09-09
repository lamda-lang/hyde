#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <runtime.h>

Value *ProtocolDecode(Byte **bytes, Error *error);
Bool ProtocolEqual(Value *protocolValue, Value *otherValue);
void ProtocolRelease(Value *protocolValue);

#endif
