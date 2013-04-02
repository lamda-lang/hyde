#ifndef RT_DECODE
#define RT_DECODE

#include "Runtime.h"

/** -brief Returns an [RTInteger8Bit] value created by decoding one byte from [data].
    -arg data The byte array.
    -return An [RTInteger8Bit] value.
    -effect [*data] points one past the byte segment that contains the value. */
RTInteger8Bit RTDecodeInteger8Bit(RTByte **data);

/** -brief Returns an [RTInteger16Bit] value created by decoding two bytes from [data] using little-endian byte order.
    -arg data The byte array.
    -return An [RTInteger16Bit] value.
    -effect [data] points one past the byte segment that contains the value. */
RTInteger16Bit RTDecodeInteger16Bit(RTByte **data);

/** -brief Returns an [RTInteger32Bit] value created by decoding four bytes from [data] using little-endian byte order.
    -arg data The byte array.
    -return An [RTInteger32Bit] value.
    -effect [*data] points one past the byte segment that contains the value. */
RTInteger32Bit RTDecodeInteger32Bit(RTByte **data);

/** -brief Returns an [RTInteger64Bit] value created by decoding eight bytes from [data] using little-endian byte order.
    -arg data The byte array.
    -return An [RTInteger64Bit] value.
    -effect [*data] points one past the byte segment that contains the value. */
RTInteger64Bit RTDecodeInteger64Bit(RTByte **data);

/** -brief Returns an [RTInteger32Bit] value created by decoding a variable number of bytes from [data] using little-endian byte order.
    -arg data The byte array.
    -return An [RTInteger32Bit] value.
    -effect [*data] points one past the byte segment that contains the value. */
RTInteger32Bit RTDecodeVBRInteger32Bit(RTByte **data);

#endif
