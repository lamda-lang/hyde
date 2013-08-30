#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "runtime.h"

VALUE *ProtocolDecode(Byte **bytes, Error *error);
void ProtocolDealloc(VALUE *protocolValue);

#endif
