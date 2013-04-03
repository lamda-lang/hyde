#ifndef RT_DECODE
#define RT_DECODE

#include "Runtime.h"

/** -brief Returns an [RTInteger8Bit] by decoding one byte from [data].
    -arg data The byte array to decode.
    -return An [RTInteger8Bit] decoded from [data].
    -effect [*data] points one past the byte segment that contains the value. */
RTInteger8Bit RTDecodeInteger8Bit(RTByte **data);

/** -brief Returns an [RTInteger16Bit] by decoding two bytes from [data] using little-endian byte order.
    -arg data The byte array to decode.
    -return An [RTInteger16Bit] decoded from [data].
    -effect [data] points one past the byte segment that contains the value. */
RTInteger16Bit RTDecodeInteger16Bit(RTByte **data);

/** -brief Returns an [RTInteger32Bit] by decoding four bytes from [data] using little-endian byte order.
    -arg data The byte array to decode.
    -return An [RTInteger32Bit] decoded from [data].
    -effect [*data] points one past the byte segment that contains the value. */
RTInteger32Bit RTDecodeInteger32Bit(RTByte **data);

/** -brief Returns an [RTInteger64Bit] by decoding eight bytes from [data] using little-endian byte order.
    -arg data The byte array to decode.
    -return An [RTInteger64Bit] decoded from [data].
    -effect [*data] points one past the byte segment that contains the value. */
RTInteger64Bit RTDecodeInteger64Bit(RTByte **data);

/** -brief Returns an [RTInteger32Bit] by decoding a variable number of bytes from [data] using little-endian byte order.
    -arg data The byte array to decode.
    -return An [RTInteger32Bit] decoded from [data].
    -effect [*data] points one past the byte segment that contains the value. */
RTInteger32Bit RTDecodeVBRInteger32Bit(RTByte **data);

#endif
