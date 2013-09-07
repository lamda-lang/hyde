#ifndef BUILTIN_PROTOCOL_H
#define BUILTIN_PROTOCOL_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *ProtocolDecode(Byte **bytes, Error *error);
void ProtocolDealloc(VALUE *protocolValue);

#endif
