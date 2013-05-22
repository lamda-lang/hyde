#ifndef DECODE_H
#define DECODE_H

#include "runtime.h"

Integer8Bit DecodeInteger8Bit(Byte **data);

Integer16Bit DecodeInteger16Bit(Byte **data);

Integer32Bit DecodeInteger32Bit(Byte **data);

Integer64Bit DecodeInteger64Bit(Byte **data);

Integer32Bit DecodeVBRInteger32Bit(Byte **data);

#endif
