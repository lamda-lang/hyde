#ifndef RT_ENCODE
#define RT_ENCODE

#include "Runtime.h"

void RTEncodeInteger8Bit(RTInteger8Bit value, RTByte **data);

void RTEncodeInteger16Bit(RTInteger16Bit value, RTByte **data);

void RTEncodeInteger32Bit(RTInteger32Bit value, RTByte **data);

void RTEncodeInteger64Bit(RTInteger64Bit value, RTByte **data);

void RTEncodeVBRInteger32Bit(RTInteger32Bit value, RTByte **data);

#endif
