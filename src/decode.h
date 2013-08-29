#ifndef DECODE_H
#define DECODE_H

#include "runtime.h"

Integer8 DecodeInteger8(Byte **bytes);
Integer32 DecodeInteger32(Byte **bytes);
Integer64 DecodeInteger64(Byte **bytes);
VALUE *DecodeValue(Byte **bytes, VALUE **error);

#endif
