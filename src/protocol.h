#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "api.h"

VALUE *ProtocolDecode(Byte **bytes, Error *error);
void ProtocolDealloc(VALUE *protocolValue);

#endif
