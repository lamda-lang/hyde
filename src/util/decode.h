#ifndef UTIL_DECODE_H
#define UTIL_DECODE_H

#include <posix/api.h>
#include <builtin/api.h>

Integer8 DecodeInteger8(Byte **bytes);
Integer32 DecodeInteger32(Byte **bytes);
Integer64 DecodeInteger64(Byte **bytes);
VALUE *DecodeValue(Byte **bytes, Error *error);

#endif
