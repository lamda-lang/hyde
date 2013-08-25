#ifndef DECODE_H
#define DECODE_H

#include "runtime.h"

Integer8 DecodeInteger8FLE(Byte **bytes);
Integer16 DecodeInteger16FLE(Byte **bytes);
Integer32 DecodeInteger32FLE(Byte **bytes);
Integer64 DecodeInteger64FLE(Byte **bytes);
Integer32 DecodeInteger32VLE(Byte **bytes);
Float64 DecodeFloat64FLE(Byte **bytes);
VALUE *DecodeValue(Byte **bytes, VALUE **error);

#endif
