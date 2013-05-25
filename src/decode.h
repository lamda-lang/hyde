#ifndef DECODE_H
#define DECODE_H

#include "api.h"

Integer8Bit DecodeInteger8BitFLE(Byte **bytes);

Integer16Bit DecodeInteger16BitFLE(Byte **bytes);

Integer32Bit DecodeInteger32BitFLE(Byte **bytes);

Integer64Bit DecodeInteger64BitFLE(Byte **bytes);

Integer32Bit DecodeInteger32BitVLE(Byte **bytes);

#endif
