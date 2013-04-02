#ifndef RT_INTEGER
#define RT_INTEGER

#include "Runtime.h"

RTInteger RTIntegerCreate(RTInteger32Bit count);

void RTIntegerDealloc(RTInteger integer);

RTSize RTIntegerEncodingSize(RTInteger integer);

void RTIntegerEncode(RTInteger integer, RTByte *buffer);

void RTIntegerDecode(RTInteger integer, RTByte **data, RTInteger32Bit count);

RTBool RTIntegerEqual(RTInteger integer, RTInteger other);

RTInteger32Bit RTIntegerHash(RTInteger integer);

#endif
