#ifndef RT_ENCODE
#define RT_ENCODE

#include "runtime.h"

/** -brief Encodes [value] into [buffer].
    -arg value The value to encode.
    -arg buffer A buffer into which to write [value].
    -effect [buffer] is overriden.
    -effect [*buffer] points one past the byte segment that contains the value. */
void RTEncodeInteger8Bit(RTInteger8Bit value, RTByte **buffer);

/** -brief Encodes [value] into [buffer] using little-endian byte order.
    -important [buffer] must be at least 2 bytes long.
    -arg value The value to encode.
    -arg buffer A buffer into which to write [value].
    -effect [buffer] is overriden.
    -effect [*buffer] points one past the byte segment that contains the value. */
void RTEncodeInteger16Bit(RTInteger16Bit value, RTByte **buffer);

/** -brief Encodes [value] into [buffer] using little-endian byte order.
    -important [buffer] must be at least 4 bytes long.
    -arg value The value to encode.
    -arg buffer A buffer into which to write [value].
    -effect [buffer] is overriden.
    -effect [*buffer] points one past the byte segment that contains the value. */
void RTEncodeInteger32Bit(RTInteger32Bit value, RTByte **buffer);

/** -brief Encodes [value] into [buffer] using little-endian byte order.
    -important [buffer] must be at least 8 bytes long.
    -arg value The value to encode.
    -arg buffer A buffer into which to write [value].
    -effect [buffer] is overriden.
    -effect [*buffer] points one past the byte segment that contains the value. */
void RTEncodeInteger64Bit(RTInteger64Bit value, RTByte **buffer);

#endif
