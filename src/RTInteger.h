#ifndef RT_INTEGER
#define RT_INTEGER

#include "Runtime.h"

void RTIntegerDealloc(RTInteger integer);

RTSize RTIntegerEncodingSize(RTInteger integer);

void RTIntegerEncode(RTInteger integer, RTByte *buffer);

RTInteger RTIntegerDecode(RTByte **data);

RTBool RTIntegerEqual(RTInteger integer, RTInteger other);

RTInteger32Bit RTIntegerHash(RTInteger integer);

RTInteger RTIntegerSum(RTInteger integer, RTInteger other);

#endif
