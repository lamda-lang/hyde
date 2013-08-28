#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "runtime.h"

VALUE *ProtocolDecode(Byte **bytes, VALUE **error);
void ProtocolDealloc(VALUE *protocolValue);

#endif
