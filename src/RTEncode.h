#ifndef RT_ENCODE
#define RT_ENCODE

#include "runtime.h"

RTError RTEncodeInteger8Bit(RTInteger8Bit value, RTBuffer *buffer);

RTError RTEncodeInteger16Bit(RTInteger16Bit value, RTBuffer *buffer);

RTError RTEncodeInteger32Bit(RTInteger32Bit value, RTBuffer *buffer);

RTError RTEncodeInteger64Bit(RTInteger64Bit value, RTBuffer *buffer);

RTError RTEncodeVBRInteger32Bit(RTInteger32Bit value, RTBuffer *buffer);

#endif
